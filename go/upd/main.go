package main

// idobata

import (
	// "fmt"

	"github.com/ganmacs/playground/go/upd/rumor"
)

func main() {
	// config := rumor.DefaultConfig()
	// config.BindAddr = "127.0.0.1"
	// config.BindPort = 3000

	// rumor, err := rumor.New(config)
	// if err != nil {
	// 	panic(err)
	// }

	// clusterSize, err := rumor.Join("127.0.0.1:3000")
	// if err != nil {
	// 	panic(err)
	// }

	// fmt.Println(clusterSize)

	// rumor.Start()

	// fmt.Println(rumor)
	rumor.ExampleMarshal()
}
