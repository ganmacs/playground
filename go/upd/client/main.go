package main

import (
	"bytes"
	"log"
	"net"
	"os"
	"time"

	"github.com/ganmacs/playground/go/upd/message"
	"gopkg.in/vmihailenco/msgpack.v2"
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

	b, err := msgpack.Marshal(&message.Alive{Name: "foo", Inc: 10})

	for i := 0; i < 10; i++ {
		conn.Write(b)
		log.Println(err)

		time.Sleep(time.Second * 1)
	}
}

func composePing() *bytes.Buffer {
	buf := bytes.NewBuffer(nil)
	// buf.WriteByte(uint8(message.PingMsg))
	return buf
}
