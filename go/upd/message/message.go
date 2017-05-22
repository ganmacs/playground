package message

import (
	"fmt"

	"gopkg.in/vmihailenco/msgpack.v2"
)

type MessageType uint8

const (
	PingMsg MessageType = iota
	AckMsg
)

type codec interface {
	Encode(interface{}) []byte
	Decode()
}

type Alive struct {
	Name string
	Inc  int
}

func (a *Alive) Encode() {
	msgpack.NewEncoder()
	// b, err := msgpack.Marshal(&Item{Foo: "bar"})
}

func ExampleMarshal() {
	if err != nil {
		panic(err)
	}

	var item Item
	err = msgpack.Unmarshal(b, &item)
	if err != nil {
		panic(err)
	}

	fmt.Println(item.Foo)
}
