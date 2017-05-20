package rumor

import (
	"net"
)

type messageType uint8

const (
	pingMsg messageType = iota
	aliveMsg
)

type message interface {
	messageType() messageType
}

type avlie struct {
	nodeName string
	addr     net.Addr
	port     int
}

func readMsgType(stream *stream) (messageType, error) {
	buf := [1]byte{0}
	if _, err := stream.Read(buf[:]); err != nil {
		return 0, err
	}

	return messageType(buf[0]), nil
}
