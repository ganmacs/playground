package main

import (
	"fmt"
	"time"

	"github.com/ganmacs/playground/go/dist/future"
)

func futureTest() {
	f := future.NewFuture(func() (future.Value, error) {
		time.Sleep(500 * time.Millisecond)
		return 1, nil
	})

	fmt.Println(f.State())

	ret, err := f.Get()

	if err == nil {
		fmt.Println(ret.(int))
	}

	fmt.Println(f.State())
}

func main() {
	futureTest()
}
