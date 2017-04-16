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

func dictWriter(done chan int, d Dict, sample map[string]int) {
	for k, v := range sample {
		d.Set(k, v)
	}

	done <- 0
}

func dictReader(done chan int, d Dict, sample map[string]int) {
	for k, _ := range sample {
		d.Get(k)
	}

	done <- 0
}

// 1 worker
func synchronizedDictWriting1() {
	doneChan := make(chan int)
	m := createSampleMap(100000)
	dict := striped.NewSynchronizedDict()

	startTime := time.Now()
	go dictWriter(doneChan, dict, m)

	<-doneChan

	fmt.Println("Elapsed Time in testSynchronizedDictWriting1:", time.Since(startTime))
}

func stripedDictWriting1() {
	doneChan := make(chan int)
	m := createSampleMap(100000)
	dict := striped.NewStripedDict()

	startTime := time.Now()
	go dictWriter(doneChan, dict, m)

	<-doneChan

	fmt.Println("Elapsed Time in testStripedDictWriting1:", time.Since(startTime))
}

// 2 wokers
func synchronizedDictWriting2() {
	doneChan := make(chan int)
	m := createSampleMap(100000)
	dict := striped.NewSynchronizedDict()

	startTime := time.Now()
	go dictWriter(doneChan, dict, m)
	go dictWriter(doneChan, dict, m)

	<-doneChan
	<-doneChan

	fmt.Println("Elapsed Time in testSynchronizedDictWriting2:", time.Since(startTime))
}

func stripedDictWriting2() {
	doneChan := make(chan int)
	m := createSampleMap(100000)
	dict := striped.NewStripedDict()

	startTime := time.Now()
	go dictWriter(doneChan, dict, m)
	go dictWriter(doneChan, dict, m)

	<-doneChan
	<-doneChan

	fmt.Println("Elapsed Time in testStripedDictWriting2:", time.Since(startTime))
}

// 5 workers
func synchronizedDictWriting5() {
	doneChan := make(chan int)
	m := createSampleMap(100000)
	dict := striped.NewSynchronizedDict()

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

	fmt.Println("Elapsed Time in testSynchronizedDictWriting5:", time.Since(startTime))
}

func stripedDictWriting5() {
	doneChan := make(chan int)
	m := createSampleMap(100000)
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

	fmt.Println("Elapsed Time in testStripedDictWriting5:", time.Since(startTime))
}

func main() {
	synchronizedDictWriting1()
	stripedDictWriting1()

	synchronizedDictWriting2()
	stripedDictWriting2()

	synchronizedDictWriting5()
	stripedDictWriting5()
}
