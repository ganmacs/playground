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

func (tr *Transport) sendMessage(msgType messageType, addr net.Addr) {
	msg, err := Encode(msgType, "")
	if err != nil {
		tr.logger.Fatal(err)
		return
	}

	tr.sendData(addr.String(), msg.Bytes())
}

func (tr *Transport) sendData(addr string, data []byte) {
	conn, err := net.Dial("udp", addr)
	if err != nil {
		tr.logger.Fatal(err)
		return
	}

	conn.Write(data)
}
