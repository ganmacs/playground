package main

import (
	"fmt"

	"github.com/ganmacs/playground/go/upd/rumor"
)

func main() {
	config := rumor.DefaultConfig()
	config.BindAddr = "127.0.0.1"

	rumor, err := rumor.New(config)
	if err != nil {
		panic(err)
	}

	fmt.Println(rumor)
}
