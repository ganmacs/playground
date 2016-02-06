package main

import (
	"fmt"
	"log"
	"runtime"
	"strconv"
	"time"
)

type Req struct {
	Color string
	Reply chan<- int
}

func newReq(color string, ch chan int) *Req {
	return &Req{Color: color, Reply: ch}
}

func sendColor(n int, color string, ch chan<- *Req) {
	in := make(chan int)
	v := newReq(color, in)
	for ; n > 0; n-- {
		ch <- v
		<-in
	}
	ch <- nil
}

func receiveColor(n int, ch <-chan *Req) {
	for n > 0 {
		if req := <-ch; req == nil {
			n--
		} else {
			fmt.Println(req.Color)
			req.Reply <- 0
		}
	}
}

func doReq() {
	ch := make(chan *Req)
	go sendColor(8, "red", ch)
	go sendColor(7, "blue", ch)
	go sendColor(6, "green", ch)
	receiveColor(3, ch)
}

func test1(n int, ch chan int, quit chan int) {
	for ; n > 0; n-- {
		ch <- n
		time.Sleep(500 * time.Millisecond)
	}
	quit <- 0
}

func test2(n int, ch chan float64, quit chan int) {
	for ; n > 0; n-- {
		ch <- float64(n)
		time.Sleep(250 * time.Millisecond)
	}
	quit <- 0
}

func test3(n int, ch chan string, quit chan int) {
	for ; n > 0; n-- {
		ch <- strconv.Itoa(n * 10)
		time.Sleep(750 * time.Millisecond)
	}
	quit <- 0
}

func doSelect() {
	ch1 := make(chan int)
	ch2 := make(chan float64)
	ch3 := make(chan string)
	quit := make(chan int)

	go test1(6, ch1, quit)
	go test2(8, ch2, quit)
	go test3(4, ch3, quit)
	for n := 3; n > 0; {
		select {
		case c := <-ch1:
			fmt.Println(c)
		case c := <-ch2:
			fmt.Println(c)
		case c := <-ch3:
			fmt.Println(c)
		case <-quit:
			n--
		default:
			fmt.Println("Non")
			time.Sleep(250 * time.Millisecond)
		}
	}
}

type Stream chan int

func makeInt(n, m int) Stream {
	s := make(Stream)
	go func() {
		for i := n; i <= m; i++ {
			s <- i
		}
		close(s)
	}()
	return s
}

func makeNum(n int) Stream {
	s := make(Stream)
	go func() {
		s <- n
	}()
	return s
}

func makeFibo() Stream {
	s := make(Stream)
	go func() {
		a, b := 1, 1
		for {
			s <- a
			a, b = b, a+b
			if a < 0 {
				break
			}
		}
		close(s)
	}()
	return s
}

func fibo(n int) int {
	if n < 2 {
		return 1
	}
	return fibo(n-2) + fibo(n-1)
}

func doFibo() {
	runtime.GOMAXPROCS(7)
	ch := make(chan int, 5)

	for _, n := range []int{37, 41, 40, 39, 38} {
		go func(x int) {
			ch <- fibo(x)
		}(n)
	}
	for i := 5; i > 0; {
		select {
		case n := <-ch:
			fmt.Println(n)
			i--
		case <-time.After(time.Second):
			fmt.Println("Timeout")
			i = 0
		}
	}
}

func worker(msg string) <-chan string {
	limit := make(chan int, 5)
	receiver := make(chan string)

	go func() {
		for i := 0; i < 100; i++ {
			log.Println(runtime.NumGoroutine())
			limit <- 1
			go func(i int) {
				msg := fmt.Sprintf("%d %s done", i, msg)
				receiver <- msg
				<-limit
			}(i)
		}
	}()
	return receiver
}

func doWorker() {
	r := worker("job")
	for i := 0; i < 100; i++ {
		log.Println(<-r)
	}
}

func doMeasure() {
	ch := make(chan int, 10)
	for n := 1; n <= 10; n++ {
		fmt.Println("-----", n, "-----")
		runtime.GOMAXPROCS(n)
		s := time.Now()
		for i := 0; i < 20; i++ {
			go func() {
				ch <- fibo(38)
			}()
		}
		for i := 20; i > 0; i-- {
			fmt.Print(<-ch, " ")
		}
		e := time.Now().Sub(s)
		fmt.Println(e)
	}
}

func f(yield chan string) {
	yield <- "one"
	yield <- "two"
	yield <- "three"
}

func doF() {
	co := make(chan string)
	go f(co)
	log.Println(<-co)
	log.Println(<-co)
	log.Println(<-co)
}

func generator(n int) chan int {
	ch := make(chan int)
	i := 0
	go func() {
		for {
			ch <- i
			i++
			if i > n {
				close(ch)
				break
			}
		}
	}()
	return ch
}

func doGen() {
	for x := range generator(10) {
		log.Println(x)
	}
}

func main() {
	// doWorker()
	// doF()
	// doGen()

	// doFibo()
	// for x := range makeFibo() {
	// 	fmt.Print(x, " ")
	// }
	// doReq()
	// doSelect()
}
