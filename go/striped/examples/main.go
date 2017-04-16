package main

import (
	"fmt"
	"time"

	"github.com/ganmacs/playground/go/striped"
)

type Dict interface {
	Get(string) int
	Set(string, int)
}

func createSampleMap(n int) map[string]int {
	m := make(map[string]int)
	k := ""

	for i := 0; i < n; i++ {
		k = fmt.Sprintf("%d", i)
		m[k] = i
	}

	return m
}

func test1() {
	doneChan := make(chan int)
	m := createSampleMap(100000)
	// dict := striped.NewSynchronizedDict()
	dict := striped.NewStripedDict()

	startTime := time.Now()
	go dictWriter(doneChan, dict, m)
	go dictWriter(doneChan, dict, m)
	go dictWriter(doneChan, dict, m)
	go dictWriter(doneChan, dict, m)
	go dictWriter(doneChan, dict, m)

	<-doneChan
	<-doneChan
	<-doneChan
	<-doneChan
	<-doneChan

	fmt.Println("Elapsed Time in test1:", time.Since(startTime))
}

func dictWriter(done chan int, d Dict, sample map[string]int) {
	for k, v := range sample {
		d.Set(k, v)
	}

	done <- 0
}

func main() {
	test1()
}
