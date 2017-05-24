package main

import (
	"log"
	"net"
	"os"

	"github.com/ganmacs/playground/go/upd/message"
	"gopkg.in/vmihailenco/msgpack.v2"
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

	a := new(message.Alive)
	msgpack.Unmarshal(buf, a)

	log.Println(a.Name)

	if message.MessageType(buf[0]) == message.PingMsg {
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
