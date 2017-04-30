package istm

import (
	"errors"
	"fmt"
)

type Transaction struct {
	varLog map[*TVar]*operation // is it better to use a defined map?
}

func NewTransaction() *Transaction {
	return &Transaction{
		varLog: make(map[*TVar]*operation),
	}
}

func (txn *Transaction) Do(f func(*Transaction) (*TVar, error)) *TVar {
	for {
		tvar, err := f(txn)

		if err != nil {
			fmt.Printf("failed at invoking closure: %v\n", err)
			txn.clear()
			continue
		}

		if err := txn.commit(); err != nil {
			fmt.Printf("failed at commit: %v\n", err)
			txn.clear()
			continue
		}

		return tvar
	}
}

func (txn *Transaction) commit() error {
	log := txn.varLog // copy
	txn.varLog = make(map[*TVar]*operation)

	readOps := make(map[*TVar]*operation)
	writeOps := make(map[*TVar]*operation)

	for tvar, op := range log {
		switch op.kind {
		case readOperation:
			tvar.mu.RLock()

			if tvar.value != op.readValue {
				tvar.mu.RUnlock()

				for tvar, _ := range readOps {
					tvar.mu.RUnlock()
				}

				for tvar, _ := range writeOps {
					tvar.mu.Unlock()
				}

				return errors.New("changed at readOperation")
			}

			readOps[tvar] = op
		case writeOperation:
			tvar.mu.Lock()

			writeOps[tvar] = op
		case readWriteOperation:
			tvar.mu.Lock()

			if tvar.value != op.readValue {
				tvar.mu.Unlock()

				for tvar, _ := range readOps {
					tvar.mu.RUnlock()
				}

				for tvar, _ := range writeOps {
					tvar.mu.Unlock()
				}

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
