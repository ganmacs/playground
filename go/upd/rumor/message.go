package rumor

import (
	"net"
)

type messageType uint8

const (
	pingMsg messageType = iota
	alivMsg
)

type message interface {
	messageType() messageType
}

type avlie struct {
	nodeName string
	addr     net.Addr
	port     int
}
