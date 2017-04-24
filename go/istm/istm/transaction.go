package istm

type Transaction struct {
	varLog map[TVar]operation // is it better to use a defined map?
}

func NewTransaction() *Transaction {
	return &Transaction{
		varLog: make(map[TVar]operation),
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
	txn.varLog = make(map[TVar]operation)

	for tvar, op := range log {
		// tvar.generation
	}

	return nil
}

func (txn *Transaction) write(tvar *TVar, v int) {
	if val, ok := txn.varLog[*tvar]; ok {
		val.write(v)
	} else {
		// tvar should be copied
		txn.varLog[*tvar] = newWriteTVarLog(v)
	}
}

func (txn *Transaction) read(tvar *TVar) int {
	if log, ok := txn.varLog[*tvar]; ok {
		return log.read()
	} else {
		value := tvar.readAtomic()
		// tvar should be copied
		txn.varLog[*tvar] = newReadTVarLog(value)
		return value
	}
}

func (txn *Transaction) clear() {
}
