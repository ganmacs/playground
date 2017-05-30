package rumor

import (
	"errors"
	"net"
)

type packet struct {
	buf []byte

	from net.Addr
}

// XXX: Is it a right place to put this method
func (p *packet) messageType() (messageType, error) {
	if len(p.buf) < 1 {
		return 0, errors.New("buf size is zero")
	}

	return messageType(p.buf[0]), nil
}

func (p *packet) Read() []byte {
	return nil
}

func (p *packet) Write(data []byte) {
}
