package main

import (
	"log"
	"net"
	"os"
)

type messageType uint8

const (
	pingMsg messageType = iota
)

type Packet struct {
	Buf []byte

	From net.Addr
}

func main() {
	startServer()
}

func startServer() {
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

	buf := make([]byte, 65536)
	log.Println("Starting server...")
	i := 0

	for {
		n, addr, err := updLn.ReadFromUDP(buf)
		log.Println("Reciveing data")
		if err != nil {
			log.Fatalln(err)
			os.Exit(1)
		}

		pcket := &Packet{Buf: buf[:n], From: addr}
		i += 1
		ch <- pcket
		go handlePacket(pcket)
		log.Println(i)
	}
}

func startHandler(ch chan *Packet) {
	for {
		c := <-ch
		handlePacket(c)
	}
}

func handlePacket(packet *Packet) {
	buf := packet.Buf
	if messageType(buf[0]) == pingMsg {
		handlePing(packet)
	} else {
		log.Fatalln("unknown message type")
	}
}

func handlePing(packet *Packet) {
	s := decode(packet.Buf[1:])
	log.Printf(s)
}

func decode(buf []byte) string {
	return string(buf[:])
}
