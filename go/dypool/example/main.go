package main

import (
	// "math/rand"
	"time"

	"github.com/ganmacs/playground/go/dypool"
)

func heavy(_ int) {
	// for i := 0; i < n; i++ {
	time.Sleep(time.Second * 2)
	// }
}

func main() {
	dpool := dypool.NewDyPool(1, 5, heavy)
	time.Sleep(time.Second * 1)

	v := 0

	for {
		dpool.Post(v)
		v += 1

		// if v%13 == 0 {
		// 	dpool.DecProcess()
		// }

		if v%10 == 0 && v < 100 {
			// dpool.IncProcess()
			dpool.IncQueue()
		}
	}
}
