package istm

func Atomically(f func(*Transaction) (int, error)) (int, error) {
	return NewTransaction().Do(f)
}
