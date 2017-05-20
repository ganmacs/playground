package state

import (
	"net"
	"time"
)

type stateType int

const (
	stateAlive stateType = iota
	stateDead
)

type Node struct {
	Addr        net.IP
	Port        uint16
	state       stateType
	StateChange time.Time
}
