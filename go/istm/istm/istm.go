package istm

func Atomically(f func(*Transaction) (*TVar, error)) int {
	return NewTxn().Do(f)
}
