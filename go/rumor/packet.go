package rumor

import (
	"net"
)

type packet struct {
	buf []byte

	from net.Addr
}

func (p *packet) Read() []byte {
	return nil
}

func (p *packet) Write(data []byte) {
}
