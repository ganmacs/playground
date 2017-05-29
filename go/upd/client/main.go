package main

import (
	"log"
	"net"
	"os"

	"github.com/ganmacs/playground/go/upd/message"
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

	msg, err := message.Encode(
		message.PingMsg,
		&message.Alive{Name: "ganmacs", Inc: 10},
	)

	if err != nil {
		os.Exit(1)
	}

	conn.Write(msg.Bytes())
}
