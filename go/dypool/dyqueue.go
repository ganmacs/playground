package dypool

import (
	"sync/atomic"
)

type dyque struct {
	size   uint32
	queue  chan int
	inCh   chan int
	stopCh chan int
}

func newDyque(size int) dyque {
	d := dyque{
		size:   uint32(size),
		queue:  make(chan int, size),
		inCh:   make(chan int, 1),
		stopCh: make(chan int, 1),
	}

	go d.startRouter()
	return d
}

func (dq *dyque) startRouter() {
	for {
		select {
		case <-dq.stopCh:
			return
		case v := <-dq.inCh:
			dq.queue <- v
		}
	}
}

func (dq *dyque) stopRouter() {
	dq.stopCh <- 1
}

func (dq *dyque) deq() chan int {
	return dq.queue
}

func (dq *dyque) enq(i int) {
	dq.inCh <- i
}

func (dq *dyque) incCapacity() error {
	dq.stopRouter()

	que := dq.queue
	defer close(que)

	s := atomic.AddUint32(&dq.size, 1)
	dq.queue = make(chan int, s)
	for i := 0; i < len(que); i++ {
		dq.queue <- <-que
	}

	go dq.startRouter()

	return nil
}

func (dq *dyque) decCapacity() error {
	dq.stopRouter()

	que := dq.queue
	defer close(que)

	s := atomic.AddUint32(&dq.size, ^uint32(0)) // sub 1
	dq.queue = make(chan int, s)
	for i := 0; i < len(que); i++ {
		dq.queue <- <-que
	}

	go dq.startRouter()

	return nil
}
