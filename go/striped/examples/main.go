package main

import (
	"fmt"

	"github.com/ganmacs/playground/go/striped"
)

func main() {
	fmt.Println("hgoe")
	dict := striped.NewStripedDict()

	dict.Set("foo", 1)
	fmt.Println(dict.Get("foo"))
}
