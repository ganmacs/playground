package main

import (
	"github.com/ganmacs/playground/go/test/lock"
	"github.com/ganmacs/playground/go/test/pointer"
	"github.com/ganmacs/playground/go/test/worker"
)

func runWorker() {
	worker.Run()
}

func runPointer() {
	pointer.Run()
}

func runLock() {
	lock.Run()
}

func main() {
	// runPointer()
	runLock()
}
