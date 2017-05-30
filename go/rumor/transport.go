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

	tcpListener *net.TCPListener
	udpListener *net.UDPConn

	shutdownCh chan int

	logger *log.Logger
}

type DefautTranportConfig struct {
	bindAddr string
	bindPort int
	logger   *log.Logger
}

func NewDefaultTransport(config *DefautTranportConfig) (*Transport, error) {
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
