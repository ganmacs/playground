package lamportc

import (
	"time"
)

type Node struct {
	clock *lclock
	conn  chan uint64
}

func NewNode(name string, interval time.Duration) *Node {
	node := &Node{
		clock: newClock(name),
		conn:  make(chan uint64),
	}

	go node.startListen()
	go node.startTick(interval)

	return node
}

func (lc *Node) Start(fn func(*Node)) {
	fn(lc)
}

func (lc *Node) WriteCurrentStep(other *Node) {
	other.conn <- lc.clock.now()
	lc.clock.tick()
}

func (lc *Node) startListen() {
	for {
		v := <-lc.conn
		go lc.clock.set(v)
	}
}

func (lc *Node) startTick(interval time.Duration) {
	c := time.Tick(interval * time.Millisecond)
	go func() {
		for {
			<-c
			go lc.clock.tick()
		}
	}()
}
