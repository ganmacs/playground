package main

import (
	"math/rand"
	"time"

	"github.com/ganmacs/playground/go/dpool"
)

func heavy(n int) {
	for i := 0; i < n; i++ {
		time.Sleep(time.Second * 5)
	}
}

func main() {
	dpool := dpool.NewDPool(10, 2, heavy)
	time.Sleep(time.Second * 1)

	v := 0

	for {
		dpool.Post(rand.Int() % 5)
		v += 1

		if v%13 == 0 {
			dpool.DecProcess()
		}

		if v%15 == 0 {
			dpool.IncProcess()
		}
	}
}
