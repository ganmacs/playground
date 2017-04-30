package istm

func Atomically(f func(*Transaction) (*TVar, error)) *TVar {
	return NewTransaction().Do(f)
}
