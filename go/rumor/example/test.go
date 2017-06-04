package main

import (
	"fmt"
	"time"

	"github.com/ganmacs/playground/go/rumor"
)

func main() {
	config := rumor.DefaultConfig()
	config.BindAddr = "127.0.0.1"
	config.BindPort = 3000

	rumor, err := rumor.New(config)
	if err != nil {
		panic(err)
	}

	clusterSize, err := rumor.Join("127.0.0.1:3000")
	if err != nil {
		panic(err)
	}

	fmt.Printf("cluster size is %d\n", clusterSize)

	rumor.Start()

	time.Sleep(time.Second * 10)
}
