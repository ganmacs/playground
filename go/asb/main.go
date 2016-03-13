package main

import (
	"fmt"
	"log"
	"reflect"
	"runtime"
	"time"
)

func ref() {
	type MyInt int
	type Chi chan int

	var x MyInt
	v := reflect.ValueOf(x)
	fmt.Println(v.Type())
	fmt.Println(v.Kind())

	// var k Chi
	// vk := reflect.ValueOf(k)
	// fmt.Println(vk.Recv())
	// fmt.Println(stat.Mode())
}

func heavyWeightJob(msg string, i int) string {
	for i := 0; i < 1000000000; i++ {
		// nope
	}
	return fmt.Sprintf("%d %s done", i, msg)
}

func test2(msg string) <-chan string {
	limit := make(chan int, 10)
	recv := make(chan string)

	go func() {
		for i := 0; i < 100; i++ {
			log.Println(runtime.NumGoroutine())
			limit <- 1
			go func(j int) {
				recv <- heavyWeightJob(msg, j)
				<-limit
			}(i)
		}
	}()

	return recv
}

func test1() {
	aaa := make(chan int)

	time.Sleep(1 * time.Second)
	fmt.Println("==================")

	go func() {
		aaa <- 1
		aaa <- 1
		aaa <- 1
		aaa <- 1
		aaa <- 1
	}()

	go func() {
		time.Sleep(1 * time.Second)
		fmt.Println(<-aaa)
		fmt.Println(<-aaa)
		fmt.Println(<-aaa)
		fmt.Println(<-aaa)
		fmt.Println(<-aaa)
	}()

	fmt.Println("------------------")
	time.Sleep(3 * time.Second)
}

func main() {
	// test1()
	recv := test2(" test 1")
	recv2 := test2(" test 2")
	recv3 := test2(" test 3")

	go func() {
		for i := 0; i < 100; i++ {
			fmt.Println(<-recv)
		}
	}()

	go func() {
		for i := 0; i < 100; i++ {
			fmt.Println(<-recv2)
		}
	}()

	for i := 0; i < 100; i++ {
		fmt.Println(<-recv3)
	}
}
