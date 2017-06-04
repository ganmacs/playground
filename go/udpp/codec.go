package udpp

import (
	"bytes"

	"gopkg.in/vmihailenco/msgpack.v2"
)

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
