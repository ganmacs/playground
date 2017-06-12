package main

import (
	"math/rand"
	"time"

	"github.com/ganmacs/playground/go/lamportc"
)

func main() {
	n1 := lamportc.NewNode()
	n2 := lamportc.NewNode()

	go n1.Start(func(node *lamportc.LNode) {
		rand.Seed(100)

		for {
			i := rand.Intn(3)
			time.Sleep(time.Second * time.Duration(i))
			n2.conn <- node.CurrentStep()
		}
	})

	go n2.Start()
	// block
}
