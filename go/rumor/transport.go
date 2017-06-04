package rumor

import (
	"log"
	"net"
)

const (
	udpPacketBufSize = 2048
)

type Transport struct {
	packetCh chan *packet

	udpListener *net.UDPConn

	shutdownCh chan int

	ackHandlers map[int]ackHandler

	logger *log.Logger
}

type TranportConfig struct {
	bindAddr string
	bindPort int
	logger   *log.Logger
}

func NewTransport(config *TranportConfig) (*Transport, error) {
	tr := &Transport{
		packetCh:   make(chan (*packet)),
		shutdownCh: make(chan (int)),
		logger:     config.logger,
	}

	addr := config.bindAddr
	ip := net.ParseIP(addr)

	if err := tr.setupUDP(ip, config.bindPort); err != nil {
		tr.logger.Println(err)
	}

	return tr, nil
}

func (tr *Transport) Start() {
	go tr.listenUDP()
}

func (tr *Transport) setupUDP(ip net.IP, port int) error {
	udpAddr := &net.UDPAddr{IP: ip, Port: port}
	udpLn, err := net.ListenUDP("udp", udpAddr)
	if err != nil {
		tr.logger.Println(err)
		return err
	}

	tr.udpListener = udpLn
	return nil
}

func (tr *Transport) listenUDP() {
	for {
		buf := make([]byte, udpPacketBufSize)

		n, addr, err := tr.udpListener.ReadFromUDP(buf)
		if err != nil {
			tr.logger.Printf("[ERROR] could not read %v", err)
			continue
		}

		tr.packetCh <- &packet{buf: buf[:n], from: addr}
	}
}

func (tr *Transport) PacketCh() chan (*packet) {
	return tr.packetCh
}

func (tr *Transport) setAckHandler(seqNo int, ch chan *ack) {
	tr.ackHandlers[seqNo] = ackHandler{ch}
}

func (tr *Transport) sendPackedMessage(addr string, msgType messageType, msg interface{}) error {
	emsg, err := Encode(msgType, msg)
	if err != nil {
		return err
	}

	if err := tr.sendData(addr, emsg.Bytes()); err != nil {
		return err
	}

	return nil
}

func (tr *Transport) sendData(addr string, data []byte) error {
	conn, err := net.Dial("udp", addr)
	if err != nil {
		return err
	}

	size, err := conn.Write(data)
	if err != nil {
		return err
	}

	if len(data) != size {
		tr.logger.Printf("failed writing data %d/%d", size, len(data))
		// return error object
	}

	return nil
}
