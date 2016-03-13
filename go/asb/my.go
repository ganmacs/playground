package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {

	c := make(chan int)

	go func() {
		wg := new(sync.WaitGroup)
		for i := 0; i <= 100; i++ {
			wg.Add(1)

			go func(i int) {
				if i%2 == 0 {
					time.Sleep(1 * time.Second)
				}
				c <- i
				wg.Done()
			}(i)
		}
		wg.Wait()
		close(c)
	}()

	cc := make(chan []int)

	go func() {
		buf := make([]int, 3, 3)
		i := 0

		for v := range c {
			buf[i] = v
			i++

			if i > 2 {
				cc <- buf
				buf = make([]int, 3, 3)
				i = 0
			}
		}

		if i != 0 {
			cc <- buf[0:i]
		}
		close(cc)
	}()

	for v := range cc {
		fmt.Println(v)
	}
}
