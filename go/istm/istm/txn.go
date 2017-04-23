package istm

type Txn struct {
}

func NewTxn() *Txn {
	return &Txn{}
}

func (txn *Txn) Do(f func(*Txn) (*TVar, error)) int {
retry:
	tvar, err := f(txn)

	if err != nil {
		txn.clear()
		goto retry
	}

	if e := tvar.commit(txn); e != nil {
		txn.clear()
		goto retry
	}

	return 0
}

func (txn *Txn) clear() {
}

func (txn *Txn) commit(tvar *TVar) error {
	return nil
}
