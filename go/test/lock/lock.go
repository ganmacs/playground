package lock

import (
	"fmt"
	"sync"
	"time"
)

type A struct {
	v int
	m sync.Mutex
}

func newA() *A {
	v := new(sync.Mutex)
	return &A{
		v: 0,
		m: *v,
	}
}

func Run() {
	a := newA()
	ch := make(chan int)

	b := *a
	c := *a

	go func(bb A) {
		fmt.Println(b.m == c.m)
		bb.m.Lock()

		fmt.Println("start bb")
		time.Sleep(time.Second * 3)
		fmt.Println("end bb")

		bb.m.Unlock()
		ch <- 0
	}(b)

	go func(cc A) {
		cc.m.Lock()

		fmt.Println("start cc")
		time.Sleep(time.Second * 3)
		fmt.Println("end cc")

		cc.m.Unlock()
		ch <- 0
	}(c)

	<-ch
	<-ch
}
