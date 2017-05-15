package main

import (
	"bytes"
	"log"
	"net"
	"os"
	"time"
)

type messageType uint8

const (
	pingMsg messageType = iota
)

func main() {
	go send()
	go send()

	send()
	time.Sleep(time.Second * 2)
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
	for i := 0; i < 100; i++ {
		conn.Write(msg.Bytes())
	}
}

func composePing() *bytes.Buffer {
	buf := bytes.NewBuffer(nil)
	buf.WriteByte(uint8(pingMsg))
	return buf
}
