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

type alive struct {
	nodeName string
	addr     string
	port     int
}
