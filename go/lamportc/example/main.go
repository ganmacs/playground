package main

import (
	"time"

	"github.com/ganmacs/playground/go/lamportc"
)

func main() {
	n1 := lamportc.NewNode("node1", 2)
	n2 := lamportc.NewNode("node2", 3)

	go n1.Start(func(node *lamportc.Node) {
		for {
			time.Sleep(time.Millisecond * 6)
			node.WriteCurrentStep(n2)
		}
	})

	go n2.Start(func(node *lamportc.Node) {
		for {
			time.Sleep(time.Millisecond * 5)
			node.WriteCurrentStep(n1)
		}
	})

	time.Sleep(time.Second * 60) // block
}
