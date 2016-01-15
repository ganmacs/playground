package main

import (
	"fmt"
	p "github.com/ganmacs/playground/go/pat/patt"
)

// a is hoge
const (
	A = iota
	B
	C
)

func main() {
	fmt.Print(B)

	fmt.Print(C)
	d := p.NewStructD("sss")
	d.P()

	f := p.GetInstane()
	f.Good()

	p.AAA()
	p.BBB()

}
