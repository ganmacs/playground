package message

import (
	"bytes"

	"gopkg.in/vmihailenco/msgpack.v2"
)

type MessageType uint8

const (
	PingMsg MessageType = iota
	AckMsg
)

// type codec interface {
// 	Encode(interface{}) []byte
// 	Decode()
// }

func Decode(buf []byte, out interface{}) error {
	r := bytes.NewReader(buf)
	dec := msgpack.NewDecoder(r)
	return dec.Decode(out)
}

func Encode(msgType MessageType, in interface{}) (*bytes.Buffer, error) {
	buf := bytes.NewBuffer(nil)
	buf.WriteByte(uint8(msgType))
	enc := msgpack.NewEncoder(buf)
	err := enc.Encode(in)
	if err != nil {
		return nil, err
	}

	return buf, nil
}

type Alive struct {
	Name string
	Inc  int
}
