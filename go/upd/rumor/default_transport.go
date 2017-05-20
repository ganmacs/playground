package rumor

import (
	"log"
	"net"
)

const (
	udpPacketBufSize = 2048
)

// implement for transport
type DefautTranport struct {
	streamCh chan net.Conn
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

func NewDefaultTransport(config *DefautTranportConfig) (*DefautTranport, error) {
	tr := &DefautTranport{
		streamCh:   make(chan (net.Conn)),
		packetCh:   make(chan (*packet)),
		shutdownCh: make(chan (int)),
		logger:     config.logger,
	}

	addr := config.bindAddr
	ip := net.ParseIP(addr)

	if err := tr.setupTCP(ip, config.bindPort); err != nil {
		tr.logger.Println(err)
	}

	if err := tr.setupUDP(ip, config.bindPort); err != nil {
		tr.logger.Println(err)
	}

	return tr, nil
}

func (tr *DefautTranport) Start() {
	go tr.listenTCP()
	go tr.listenUDP()
}

func (tr *DefautTranport) setupTCP(ip net.IP, port int) error {
	tcpAddr := &net.TCPAddr{IP: ip, Port: port}
	tcpLn, err := net.ListenTCP("tcp", tcpAddr)
	if err != nil {
		tr.logger.Println(err)
		return err
	}

	tr.tcpListener = tcpLn
	return nil
}

func (tr *DefautTranport) setupUDP(ip net.IP, port int) error {
	udpAddr := &net.UDPAddr{IP: ip, Port: port}
	udpLn, err := net.ListenUDP("udp", udpAddr)
	if err != nil {
		tr.logger.Println(err)
		return err
	}

	tr.udpListener = udpLn
	return nil
}

func (tr *DefautTranport) listenTCP() {
	for {
		conn, err := tr.tcpListener.AcceptTCP()
		if err != nil {
			tr.logger.Printf("[ERROR] could not accept %v", err)
			continue
		}

		tr.streamCh <- conn
	}
}

func (tr *DefautTranport) listenUDP() {
	for {
		buf := make([]byte, udpPacketBufSize)

		n, addr, err := tr.udpListener.ReadFromUDP(buf)
		if err != nil {
			tr.logger.Printf("[ERROR] could not accept %v", err)
			continue
		}

		tr.packetCh <- &packet{buf: buf[:n], from: addr}
	}
}

func (tr *DefautTranport) StreamCh() chan (net.Conn) {
	return tr.streamCh
}

func (tr *DefautTranport) PacketCh() chan (*packet) {
	return tr.packetCh
}
