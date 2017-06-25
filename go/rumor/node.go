package rumor

import (
	"net"
	"strconv"
	"time"
)

type Node struct {
	name string
	addr string
	port int

	incarnation uint64
	stateType   stateType
	stateChange time.Time
}

func (nd *Node) Address() string {
	return net.JoinHostPort(nd.addr, strconv.Itoa(nd.port))
}

func (nd *Node) aliveNode() {
	if nd.stateType == aliveState {
		return
	}

	nd.stateType = aliveState
	nd.stateChange = time.Now()
}

func (nd *Node) deadNode() {
	if nd.stateType == deadState {
		return
	}

	nd.stateType = deadState
	nd.stateChange = time.Now()
}
