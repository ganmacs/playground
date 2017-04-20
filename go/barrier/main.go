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
		n := int(b.num)
		for i := 1; i < n; i++ {
			b.c <- 0
		}
	} else {
		<-b.c
	}
}

func Process(n int, b CyclicBarrier, c chan int) {
	fmt.Printf("[Start] Process%d\n", n)

	time.Sleep(time.Second * time.Duration(n)) // your code

	fmt.Printf("[Wait] Process%d\n", n)
	b.Wait()

	fmt.Printf("[Done] Process%d\n", n)
	c <- 0
}

func main() {
	b := NewCyclicBarrier(4)
	c := make(chan int)

	go Process(1, *b, c)
	go Process(2, *b, c)
	go Process(4, *b, c)
	go Process(3, *b, c)

	<-c
	<-c
	<-c
	<-c
}
