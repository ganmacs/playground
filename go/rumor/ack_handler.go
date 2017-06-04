package rumor

type ackHandler struct {
	ch chan *ack
}

func (p *ackHandler) handle() {
}
