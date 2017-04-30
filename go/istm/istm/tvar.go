package istm

import (
	"sync"
)

type TVar struct {
	value int
	mu    *sync.RWMutex
}

func NewTVar(v int) *TVar {
	return &TVar{
		value: v,
		mu:    new(sync.RWMutex),
	}
}

func (t *TVar) Read(txn *Transaction) int {
	return txn.read(t)
}

func (t *TVar) Write(txn *Transaction, v int) { // result?
	txn.write(t, v)
}

func (t *TVar) readAtomic() int {
	t.mu.RLock()
	defer t.mu.RUnlock()

	return t.value
}
