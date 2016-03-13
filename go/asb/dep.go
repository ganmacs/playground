package main

import (
	"fmt"
	"sync"
)

func buildJob(s string) chan string {
	buff := make(chan string)
	var wg sync.WaitGroup

	go func() {
		for i := 0; i < 100; i++ {
			wg.Add(1)
			msg := fmt.Sprintf("%d %s", i, s)

			go func(msg string) {
				fmt.Println("Start: " + msg)

				for i := 0; i < 10000000; i++ {
					// noop
				}

				buff <- msg
				wg.Done()
			}(msg)
		}

		wg.Wait()
		close(buff)
	}()

	return buff
}

func processA(in chan string) chan string {
	out := make(chan string)

	go func() {
		go func() {
			for {
				receive, ok := <-in

				if !ok {
					close(out)
					break
				}

				go func(s string) {
					for i := 0; i < 1000000000; i++ {
						// noop
					}

					fmt.Println("Processed " + receive)
					out <- s
				}(receive)
			}
		}()
	}()
	return out
}

func main() {
	outA := buildJob("job A")
	pOutA := processA(outA)

	for i := 0; i < 100; i++ {
		fmt.Println("Done " + <-pOutA)
	}
}
