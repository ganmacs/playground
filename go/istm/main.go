package main

import (
	"fmt"
	"time"

	"github.com/ganmacs/playground/go/istm/istm"
)

func main() {
	tvar := istm.NewTVar(10)

	go func() {
		tv, _ := istm.Atomically(func(t *istm.Transaction) (int, error) {
			v := tvar.Read(t)
			tvar.Write(t, v+1)
			return v, nil
		})

		fmt.Printf("t1: %v\n", tv)
	}()

	go func() {
		tv, _ := istm.Atomically(func(t *istm.Transaction) (int, error) {
			v := tvar.Read(t)
			tvar.Write(t, v+2)
			return v, nil
		})

		fmt.Printf("t2: %v\n", tv)
	}()

	// go func() {
	// tv, _ := istm.Atomically(func(t *istm.Transaction) (int, error) {
	// 		time.Sleep(time.Millisecond * 10)
	// 		v := tvar.Read(t)
	// 		return v, nil
	// 	})

	// 	fmt.Printf("t3: %v\n", tv)
	// }()

	// go func() {
	// 	tv, _ := istm.Atomically(func(t *istm.Transaction) (int, error) {
	// 		v := tvar.Read(t)
	// 		tvar.Write(t, v+100)
	// 		return v, nil
	// 	})
	// 	fmt.Printf("t4: %v\n", tv)
	// }()

	time.Sleep(time.Second * 2)
	fmt.Printf("last: %v\n", tvar)
}
