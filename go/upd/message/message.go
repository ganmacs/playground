package message

// import (
// 	"fmt"
// 	"io"

// 	"gopkg.in/vmihailenco/msgpack.v2"
// )

type MessageType uint8

const (
	PingMsg MessageType = iota
	AckMsg
)

// type codec interface {
// 	Encode(interface{}) []byte
// 	Decode()
// }

type Alive struct {
	Name string
	Inc  int
}

// func (a *Alive) Encode() {
// }

// func ExampleMarshal() {
// 	if err != nil {
// 		panic(err)
// 	}

// 	var item Item
// 	err = msgpack.Unmarshal(b, &item)
// 	if err != nil {
// 		panic(err)
// 	}

// 	fmt.Println(item.Foo)
// }
