package istm

import (
	"errors"
)

var TransactionAborted = errors.New("Transction Aborted")

type Transaction struct {
	varLog map[*TVar]*operation
}

func NewTransaction() *Transaction {
	return &Transaction{
		varLog: make(map[*TVar]*operation),
	}
}

func (txn *Transaction) Run(f func(*Transaction) (int, error)) (int, error) {
	for {
		tvar, err := f(txn)

		if err != nil {
			txn.clear()
			if err == TransactionAborted {
				continue
			}
			return 0, err
		}

		if err := txn.commit(); err != nil {
			txn.clear()
			if err == TransactionAborted {
				continue
			}
			return 0, err
		}

		return tvar, nil
	}
}

func (txn *Transaction) commit() error {
	readOps := make(map[*TVar]*operation)
	writeOps := make(map[*TVar]*operation)

	defer func() {
		for tvar, _ := range readOps {
			tvar.mu.RUnlock()
		}

		for tvar, _ := range writeOps {
			tvar.mu.Unlock()
		}
	}()

	for tvar, op := range txn.varLog {
		switch op.kind {
		case readOperation:
			tvar.mu.RLock()

			if tvar.value != op.readValue {
				tvar.mu.RUnlock()
				return TransactionAborted
			}

			readOps[tvar] = op
		case writeOperation:
			tvar.mu.Lock()

			writeOps[tvar] = op
		case readWriteOperation:
			tvar.mu.Lock()

			if tvar.value != op.readValue {
				tvar.mu.Unlock()
				return TransactionAborted
			}

			writeOps[tvar] = op
		}
	}

	for tvar, log := range writeOps {
		tvar.value = log.writeValue // commit
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
