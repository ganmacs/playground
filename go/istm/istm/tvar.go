package istm

import (
	"sync"
)

type TVar struct {
	generation int32
	value      int
	mu         *sync.RWMutex
}

func NewTVar(v int) *TVar {
	return &TVar{
		generation: 0,
		value:      v,
		mu:         new(sync.RWMutex),
	}
}

func (t *TVar) Read(txn *Transaction) int {
	return txn.read(t)
}

func (t *TVar) Write(txn *Transaction, v int) { // result?
	txn.write(t, v)
}

func (t *TVar) readAtomic() int {
	t.mu.Lock()
	defer t.mu.Unlock()

	return t.value
}

func (t *TVar) toKey() {
}

func (t *TVar) nextGenration() {
	t.generation++ // atomic?
}
