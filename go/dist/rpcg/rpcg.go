package rpcg

import (
	"net"
)

func Foo() {
	net.Listen("tcp", "localhost:8000")
}
