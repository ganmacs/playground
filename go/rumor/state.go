package rumor

import (
	"sync/atomic"
)

type stateType int

const (
	aliveState stateType = iota
	deadState
)

func (ru *Rumor) Tick() uint64 {
	return atomic.AddUint64(&ru.Incarnation, 1)
}
