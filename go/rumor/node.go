package rumor

import (
	"time"
)

type Node struct {
	name string
	addr string

	incarnation uint64
	stateType   stateType
	stateChange time.Time
}

func (nd *Node) Address() string {
	return nd.addr
}

func (nd *Node) aliveNode() {
	if nd.stateType == aliveState {
		return
	}

	nd.stateType = aliveState
	nd.stateChange = time.Now()
}

func (nd *Node) suspectedNode() {
	if nd.stateType == suspectedState {
		return
	}

	nd.stateType = suspectedState
	nd.stateChange = time.Now()
}
