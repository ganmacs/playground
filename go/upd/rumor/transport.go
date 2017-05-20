package rumor

import (
	"net"
)

type packet struct {
	buf []byte

	from net.Addr
}

// transpor is a interface to be testable
type Transport interface {
	StreamCh() chan (net.Conn)

	PacketCh() chan (*packet)

	Start()
}
