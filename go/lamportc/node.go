package lamportc

import (
	"time"
)

type LNode struct {
	clock *lclock
	conn  chan uint64
}

func NewNode() *LNode {
	node := &LNode{
		clock: newClock(),
		conn:  make(chan uint64),
	}

	go node.startListen()
	startTick(node.nextStep, 1*time.Second)

	return node
}

func (lc *LNode) Start(fn func(*LNode)) {
	fn(lc)
}

func (lc *LNode) CurrentStep() uint64 {
	return lc.clock.step
}

func (lc *LNode) nextStep() {
	lc.clock.tick()
}

func (lc *LNode) setStep(v uint64) {
	lc.clock.set(v)
}

func (lc *LNode) startListen() {
	for {
		v := <-lc.conn
		go lc.setStep(v)
	}
}

func startTick(fn func(), t time.Duration) {
	c := time.Tick(t)

	go func() {
		<-c
		go fn()
	}()
}
