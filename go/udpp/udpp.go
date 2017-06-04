package udpp

import (
	"bytes"
	"encoding/binary"
	"log"
)

// 1 byte
type MessageType uint8

const (
	PingMsg MessageType = iota
	JoinMsg
	CompoundMsg
)

type Join struct {
	Name string
}

type Ping struct {
	Name string
}

func ComposeCompoundMessage(msgs [][]byte) *bytes.Buffer {
	log.Println("Composing compound message")
	buf := bytes.NewBuffer(nil)

	// message type is 1 byte
	buf.WriteByte(uint8(CompoundMsg))

	// message count is 1 byte
	buf.WriteByte(uint8(len(msgs)))

	for _, msg := range msgs {
		// message size is 2bytes
		binary.Write(buf, binary.BigEndian, uint16(len(msg)))
	}

	for _, msg := range msgs {
		buf.Write(msg)
	}

	return buf
}

func decomposeCompoundMessage(buf []byte) ([][]byte, error) {
	log.Println("Decomposing compound message")

	msgCount := uint8(buf[0]) // 1bytes
	buf = buf[1:]

	lengths := make([]uint16, msgCount) // 2bytes
	for i := 0; i < int(msgCount); i++ {
		lengths[i] = binary.BigEndian.Uint16(buf[i*2 : i*2+2])
	}

	buf = buf[msgCount*2:]

	result := make([][]byte, 0)

	for _, msgLen := range lengths {
		slice := buf[:msgLen]
		buf = buf[msgLen:]
		result = append(result, slice)
	}

	return result, nil
}

func Handle(buf []byte) {
	msgType := MessageType(buf[0])

	switch msgType {
	case PingMsg:
		handlePing(buf[1:])
	case JoinMsg:
		handleJoin(buf[1:])
	case CompoundMsg:
		handleCompound(buf[1:])
	default:
		log.Printf("Unknow message type %d", msgType)
	}
}

func handleCompound(buf []byte) {
	log.Println("Receiving compound mesage ")
	msgs, err := decomposeCompoundMessage(buf)
	if err != nil {
		log.Print(err)
		return
	}

	for _, msg := range msgs {
		Handle(msg)
	}
}

func handlePing(buf []byte) {
	var msg = new(Ping)
	err := Decode(buf, &msg)
	if err != nil {
		log.Println(err)
	}

	log.Printf("Receiving PING mesage %v\n", msg)
}

func handleJoin(buf []byte) {
	var msg = new(Join)
	err := Decode(buf, &msg)
	if err != nil {
		log.Println(err)
	}

	log.Printf("Receiving JOIN mesage %v\n", msg)
}
