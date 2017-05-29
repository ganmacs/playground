package main

import (
	"log"
	"net"
	"os"

	"github.com/ganmacs/playground/go/upd/message"
)

type Packet struct {
	Buf []byte

	From net.Addr
}

// start sever
func main() {
	ch := make(chan *Packet)

	udpAddr := &net.UDPAddr{
		IP:   net.ParseIP("127.0.0.1"),
		Port: 8080,
	}

	updLn, err := net.ListenUDP("udp", udpAddr)
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}

	go startHandler(ch)

	buf := make([]byte, 65536)
	log.Println("Starting server...")

	for {
		n, addr, err := updLn.ReadFromUDP(buf)
		log.Println("Reciveing data")
		if err != nil {
			log.Fatalln(err)
			os.Exit(1)
		}

		pcket := &Packet{Buf: buf[:n], From: addr}
		ch <- pcket
	}
}

func startHandler(ch chan *Packet) {
	for {
		select {
		case c := <-ch:
			go handlePacket(c)
			// select timeout
		}
	}
}

func handlePacket(packet *Packet) {
	buf := packet.Buf

	msgType := message.MessageType(buf[0])
	packt := &Packet{Buf: buf[1:], From: packet.From}

	switch msgType {
	case message.PingMsg:
		handlePing(packt)
	default:
		log.Println("nothing")
	}
}

func handlePing(packet *Packet) {
	var msg = new(message.Alive)
	err := message.Decode(packet.Buf, msg)
	if err != nil {
		log.Fatalln(err)
	}

	log.Println(msg)
}
