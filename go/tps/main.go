package main

import (
	"fmt"
	"runtime"
)

type afunc func(a string) (string, int)
type A struct {
	No int
	S  string
}

func main() {
	// bb := []byte("a\n")
	// fmt.Println(bb)

	// aaa(func(a string) (string, int) {
	// 	return a, 1
	// })
	// co()
	// bbb()
}

// func ainter(a Behaivor) {
// 	f := a.Foo()
// 	fmt.Println(f)
// }

type Behaivor interface {
	Foo()
}

func (s *A) Foo() string {
	return "saiaku"
}

func bbb() {
	a := make(chan A)

	go func() {
		var f A
		f.No = 1
		a <- f
	}()

	k := <-a
	if k.S == "" {
		fmt.Println(k.No)
	} else {
		fmt.Println("asdkfja;ldsfka;")
	}

}

func aaa(a afunc) {
	b, c := a("asdf")
	fmt.Println(b)
	fmt.Println(c)
}

func co() {
	co := make(chan string)
	go fco(co)
	fmt.Println("ffff")
	d := <-co
	fmt.Println(d)
}

func fco(y chan string) {
	y <- "one"
	y <- "two"
}

func lchan(c chan int) {
	for out := range c {
		fmt.Println(
			fmt.Sprintf("out from => %d", out),
		)
	}
}

func fff() {
	fmt.Println("main stared now")

	myChan := make(chan int)
	go lchan(myChan)

	for i := 0; i < 100000; i++ {
		myChan <- i
	}

	fmt.Println("main exited now")
}

func foo() {
	if cpu := runtime.NumCPU(); cpu == 1 {
		fmt.Println(cpu)
	} else {
		fmt.Println(cpu)
	}

	var a []string

	for _, c := range []string{"a", "c"} {
		a = append(a, c)
	}
	d := []byte("sfsfd")

	fmt.Println(d)
}
