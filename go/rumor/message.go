package rumor

type messageType uint8

const (
	pingMsg messageType = iota
	aliveMsg
	ackMsg
)

type message interface {
	messageType() messageType
}

type ping struct {
	name string
	id   int
}

type ack struct {
	name string
	id   int
}

type alive struct {
	nodeName string
	addr     string
	port     int
}
