package rumor

import (
	"time"
)

type node struct {
	name        string
	addr        string
	port        int
	stateType   stateType
	stateChange time.Time
}

func (node *node) Address() string {
	return node.addr
}

func (node *node) AliveState() {
	if node.stateType == aliveState {
		return
	}

	node.stateType = aliveState
	node.stateChange = time.Now()
}
