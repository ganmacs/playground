package rumor

type messageType uint8

const (
	pingMsg messageType = iota
	aliveMsg
)

type message interface {
	messageType() messageType
}

type alive struct {
	nodeName string
	addr     string
	port     int
}

func readMsgType(stream *stream) (messageType, error) {
	buf := [1]byte{0}
	if _, err := stream.Read(buf[:]); err != nil {
		return 0, err
	}

	return messageType(buf[0]), nil
}
