package rumor

import (
	"bytes"
	"encoding/binary"
)

const (
	compoundMsgSizeOverhead = 2 // 2 bytes
)

type messageType uint8

const (
	pingMsg messageType = iota
	ackMsg
	pingReqMsg

	aliveMsg

	compoundMsg
)

type ping struct {
	Name string
	Id   int
	Addr string
}

type ack struct {
	Name string
	Id   int
	Addr string
}

type pingReq struct {
	Id       int
	FromName string
	ToAddr   string
}

type alive struct {
	Name        string
	Addr        string
	Incarnation uint64
}

func ComposeCompoundMessage(msgs [][]byte) *bytes.Buffer {
	buf := bytes.NewBuffer(nil)

	// message type is 1 byte
	buf.WriteByte(uint8(compoundMsg))

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
