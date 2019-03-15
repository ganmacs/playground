package main

import (
	"bytes"
	"github.com/ganmacs/playground/go/bbb/msgpack"
	// "fmt"
	// "os"
)

type A struct {
	buf *bytes.Buffer
	enc *msgpack.Encoder
	dec *msgpack.Decoder
}

func (t *A) set() {
	t.buf = &bytes.Buffer{}
	t.enc = msgpack.NewEncoder(t.buf)
	t.dec = msgpack.NewDecoder(t.buf)
}

func main() {
	a := &A{}
	a.set()
	a.enc.Encode(1)
	a.enc.Encode(true)
}
