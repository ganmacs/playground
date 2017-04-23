package istm

type TVar struct {
	value int
}

func NewTVar(v int) *TVar {
	return &TVar{
		value: v,
	}
}

func (t *TVar) Read(txn *Txn) int {
	return 0
}

func (t *TVar) Write(txn *Txn, v int) {

}

func (t *TVar) commit(txn *Txn) error {
	return txn.commit(t)
}
