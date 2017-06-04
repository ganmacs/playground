package main

import (
	"log"
	"net"
	"os"

	"github.com/ganmacs/playground/go/udpp"
)

func main() {
	send()
}

func send() {
	conn, err := net.Dial("udp", "127.0.0.1:8080")
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}
	defer conn.Close()

	// compose compund message
	msg1, err := udpp.Encode(udpp.PingMsg, &udpp.Ping{Name: "ganmacs"})
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}

	msg2, err := udpp.Encode(udpp.JoinMsg, &udpp.Join{Name: "ganmacs"})
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}

	msg := udpp.ComposeCompoundMessage([][]byte{
		msg1.Bytes(),
		msg2.Bytes(),
	})

	log.Println("Seding messages...")
	conn.Write(msg.Bytes())
}
