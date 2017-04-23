package istm

func Atomically(f func(*Txn) (*TVar, error)) int {
	return NewTxn().Do(f)
}
