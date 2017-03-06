package main

import (
	"fmt"
	"time"

	"github.com/ganmacs/playground/go/dist/future"
	"github.com/ganmacs/playground/go/dist/pool"
	"github.com/ganmacs/playground/go/dist/rpcg"
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

func promiseTest() {
	fmt.Println("===Start promiseTest===")

	promise := future.NewPromise(func() (future.Value, error) {
		fmt.Println("start Promsie")
		time.Sleep(500 * time.Millisecond)
		return 1, nil
	}).Then(func(value future.Value) (future.Value, error) {
		fmt.Println("promise then")
		v := value.(int)
		time.Sleep(500 * time.Millisecond)
		return v + 1, nil
	}).Then(func(value future.Value) (future.Value, error) {
		fmt.Println("promise then")
		v := value.(int)
		time.Sleep(500 * time.Millisecond)
		return v + 1, nil
	})

	value, err := promise.Get()

	if err == nil {
		fmt.Println(value.(int))
	}

}

func rpcTest() {
	rpcg.Foo()
}

func main() {
	// futureTest()
	// promiseTest()
	// rpcTest()
	pool.Run()
}
