package main

import (
	"github.com/ganmacs/playground/go/test/pointer"
	"github.com/ganmacs/playground/go/test/worker"
)

func runWorker() {
	worker.Run()
}

func runPointer() {
	pointer.Run()
}

func main() {
	runPointer()
}
