package istm

import (
	"errors"
)

type Transaction struct {
	varLog map[*TVar]*operation // is it better to use a defined map?
}

func NewTransaction() *Transaction {
	return &Transaction{
		varLog: make(map[*TVar]*operation),
	}
}

func (txn *Transaction) Do(f func(*Transaction) (*TVar, error)) int {
retry:
	tvar, err := f(txn)

	if err != nil {
		txn.clear()
		goto retry
	}

	if err := txn.commit(); err != nil {
		txn.clear()
		goto retry
	}

	return tvar.readAtomic() // ok?
}

func (txn *Transaction) commit() error {
	// should lock
	log := txn.varLog // copy
	txn.varLog = make(map[*TVar]*operation)

	readOps := make(map[*TVar]*operation)
	writeOps := make(map[*TVar]*operation)

	for tvar, op := range log {
		switch op.kind {
		case readOperation:
			tvar.mu.RLock()

			if tvar.value != op.readValue {
				return errors.New("changed at readOperation")
			}
			readOps[tvar] = op
		case writeOperation:
			tvar.mu.Lock()

			writeOps[tvar] = op
		case readWriteOperation:
			tvar.mu.Lock()

			if tvar.value != op.readValue {
				return errors.New("changed at readWriteOperation")
			}
			writeOps[tvar] = op
		}
	}

	for tvar, _ := range readOps {
		tvar.mu.RUnlock()
	}

	for tvar, log := range writeOps {
		tvar.value = log.writeValue // commit
		tvar.mu.Unlock()
	}

	return nil
}

func (txn *Transaction) write(tvar *TVar, v int) {
	if op, ok := txn.varLog[tvar]; ok {
		op.write(v)
	} else {
		txn.varLog[tvar] = newWriteTVarLog(v)
	}
}

func (txn *Transaction) read(tvar *TVar) int {
	if op, ok := txn.varLog[tvar]; ok {
		return op.read()
	} else {
		ret := tvar.readAtomic()
		txn.varLog[tvar] = newReadTVarLog(ret)
		return ret
	}
}

func (txn *Transaction) clear() {
	txn.varLog = make(map[*TVar]*operation)
}
