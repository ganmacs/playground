package main

import (
	"fmt"
	"strconv"
	"time"
)

func worker(cap int) chan int {
	c := make(chan int, cap)

	go func() {
		for i := 0; i < 100; i++ {
			fmt.Println("push " + strconv.Itoa(i))
			c <- i
		}
		close(c)
	}()

	return c
}

func main() {
	c := worker(10)

	for v := range c {
		time.Sleep(1 * time.Second)
		fmt.Println(v)
	}
}
