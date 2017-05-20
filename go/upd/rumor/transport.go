package rumor

// transpor is a interface to be testable
type Transport interface {
	StreamCh() chan (*stream)

	PacketCh() chan (*packet)

	Start()
}
