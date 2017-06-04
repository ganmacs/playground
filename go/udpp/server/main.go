package main

import (
	"log"
	"net"
	"os"

	"github.com/ganmacs/playground/go/udpp"
)

func main() {
	ch := make(chan []byte)

	udpAddr := &net.UDPAddr{
		IP:   net.ParseIP("127.0.0.1"),
		Port: 8080,
	}

	updLn, err := net.ListenUDP("udp", udpAddr)
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}

	go startPacketHandler(ch)

	buf := make([]byte, 65536)
	log.Println("Starting server...")

	for {
		n, addr, err := updLn.ReadFromUDP(buf)
		log.Printf("Reciveing data from : %s", addr)
		if err != nil {
			log.Fatalln(err)
			os.Exit(1)
		}

		ch <- buf[:n]
	}
}

func startPacketHandler(ch chan []byte) {
	for {
		udpp.Handle(<-ch)
	}
}
