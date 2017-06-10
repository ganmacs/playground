package rumor

import (
	"net"
	"strconv"
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
	return net.JoinHostPort(node.addr, strconv.Itoa(node.port))
}

func (node *node) AliveState() {
	if node.stateType == aliveState {
		return
	}

	node.stateType = aliveState
	node.stateChange = time.Now()
}
