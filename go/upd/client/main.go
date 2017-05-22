package main

import (
	"bytes"
	"log"
	"net"
	"os"
	"time"

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
	msg := composePing()

	msg.WriteString("hello this is it")
	for i := 0; i < 10; i++ {
		conn.Write(msg.Bytes())
		time.Sleep(time.Second * 1)
	}
}

func composePing() *bytes.Buffer {
	buf := bytes.NewBuffer(nil)
	buf.WriteByte(uint8(message.PingMsg))
	return buf
}
