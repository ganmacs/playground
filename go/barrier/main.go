package main

import (
	"fmt"
	"sync/atomic"
	"time"
)

type CyclicBarrier struct {
	num       int32
	waitCount int32
	c         chan int
}

func NewCyclicBarrier(num int) *CyclicBarrier {
	return &CyclicBarrier{
		num:       int32(num),
		waitCount: 0,
		c:         make(chan int),
	}
}

func (b *CyclicBarrier) Wait() {
	atomic.AddInt32(&b.waitCount, 1)

	if atomic.LoadInt32(&b.waitCount) == b.num {
		b.broadcast()
	} else {
		<-b.c
	}
}

func (b *CyclicBarrier) broadcast() {
	n := int(b.num)
	for i := 1; i < n; i++ {
		b.c <- 0
	}
}

func Process(n int, b *CyclicBarrier) {
	fmt.Printf("[Start] Process %d\n", n)

	time.Sleep(time.Second * time.Duration(n))

	fmt.Printf("[Wait] Process %d\n", n)
	b.Wait()
}

func main() {
	b := NewCyclicBarrier(3)

	go Process(4, b)
	go Process(1, b)
	go Process(2, b)

	Process(3, b)
	fmt.Println("Done!")
}
