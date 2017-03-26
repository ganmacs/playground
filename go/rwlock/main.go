package main

import (
	"fmt"
	"sync"
	"time"
)

type RW struct {
	cond       sync.Cond
	mutex      *sync.Mutex
	readerWait int
	writerWait bool
}

func NewRWLock() *RW {
	var m = &sync.Mutex{}
	return &RW{
		cond:       sync.Cond{L: m},
		mutex:      m,
		readerWait: 0,
		writerWait: false,
	}
}

func (lock *RW) RLock() {
	lock.mutex.Lock()

	if lock.writerWait {
		lock.cond.Wait()
	}

	lock.readerWait++
	lock.mutex.Unlock()
}

func (lock *RW) RUnlock() {
	lock.mutex.Lock()

	if lock.readerWait == 1 {
		lock.cond.Signal()
	}

	lock.readerWait--
	lock.mutex.Unlock()
}

func (lock *RW) Lock() {
	lock.mutex.Lock()

	if lock.writerWait || lock.readerWait > 0 {
		lock.cond.Wait()
	}

	lock.writerWait = true
	lock.mutex.Unlock()
}

func (lock *RW) Unlock() {
	lock.mutex.Lock()

	lock.cond.Broadcast()

	lock.writerWait = false
	lock.mutex.Unlock()
}

func main() {
	i := 0
	var ch = make(chan int)
	m := NewRWLock()
	lim1 := 5000
	lim2 := 100
	lim := lim1 + lim2

	start := time.Now()

	for l := 0; l < lim1; l++ {
		go func() {
			m.RLock()
			// fmt.Println(i)
			m.RUnlock()
			ch <- 1
		}()
	}

	for l := 0; l < lim2; l++ {
		go func(vv int, cc chan int) {
			m.Lock()
			i += vv
			time.Sleep(100 * time.Millisecond)
			m.Unlock()
			cc <- vv
		}(l, ch)
	}

	ret := 0
	for l := 0; l < lim; l++ {
		ret += <-ch
	}

	elapsed := time.Since(start)
	fmt.Printf("took %s\n", elapsed)

	fmt.Println(i)
	fmt.Println(ret)
}
