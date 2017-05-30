package rumor

import (
	"time"
)

type node struct {
	addr        string
	port        int
	stateType   stateType
	stateChange time.Time
}

func (node *node) AliveState() {
	if node.stateType == aliveState {
		return
	}

	node.stateType = aliveState
	node.stateChange = time.Now()
}
