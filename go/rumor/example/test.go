package main

import (
	"fmt"
	"os"
	"strconv"
	"time"

	"github.com/ganmacs/playground/go/rumor"
	"github.com/ganmacs/playground/go/rumor/logger"
)

func main() {
	sport := os.Getenv("PORT")
	port, _ := strconv.Atoi(sport)

	config := rumor.DefaultConfig()
	config.BindAddr = "127.0.0.1"
	config.BindPort = port

	config.Logger = logger.NewLevelLogger(os.Stdout, logger.INFO)

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

	time.Sleep(time.Second * 1000)
}
