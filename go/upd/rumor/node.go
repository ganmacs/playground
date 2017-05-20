package rumor

import (
	"net"
)

type node struct {
	stateType stateType
	addr      net.Addr
	port      int
}
