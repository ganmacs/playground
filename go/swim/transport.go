package swim

import (
	"fmt"
	"net"
	"os"
)

type Transport struct {
	streamCh chan net.Conn
}

func (t *Transport) ListenTCP(tcpLn *net.TCPListener) {
	for {
		conn, err := tcpLn.AcceptTCP()
		if err != nil {
			fmt.Println("Can't resolve tcp address: ", err)
			os.Exit(1)
		}

		t.streamCh <- conn
	}
}

func NewTransport() *Transport {
	t := &Transport{
		streamCh: make(chan net.Conn),
	}

	tcpAddr, err := net.ResolveTCPAddr("tcp", ADDR)
	if err != nil {
		fmt.Println("Can't resolve tcp address: ", err)
		os.Exit(1)
	}

	tcpLn, err := net.ListenTCP("tcp", tcpAddr)
	if err != nil {
		fmt.Println("Can't listen: ", err)
		os.Exit(1)
	}

	go t.ListenTCP(tcpLn)

	return t
}
