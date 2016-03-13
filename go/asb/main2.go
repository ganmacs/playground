package main

import (
	"fmt"
	"time"
)

func main() {
	c := make(chan int, 5)

	go func() {
		for i := 0; i < 100; i++ {
			fmt.Println("push 1")
			c <- 1
		}
	}()

	go func() {
		for i := 0; i < 50; i++ {
			fmt.Println(fmt.Sprintf("%d in go routine", <-c))
			fmt.Println(<-c)
			time.Sleep(1 * time.Second)
		}
	}()

	for i := 0; i < 50; i++ {
		fmt.Println(fmt.Sprintf("%d in main", <-c))
		time.Sleep(1 * time.Second)
	}

}
