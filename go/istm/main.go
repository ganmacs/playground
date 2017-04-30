package main

import (
	"fmt"
	"time"

	"github.com/ganmacs/playground/go/istm/istm"
)

func main() {
	tvar := istm.NewTVar(10)

	go func() {
		tv := istm.Atomically(func(t *istm.Transaction) (*istm.TVar, error) {
			v := tvar.Read(t)
			tvar.Write(t, v+1)
			return tvar, nil
		})

		fmt.Printf("t1: %v\n", tv)
	}()

	go func() {
		tv := istm.Atomically(func(t *istm.Transaction) (*istm.TVar, error) {
			v := tvar.Read(t)
			tvar.Write(t, v+1)
			return tvar, nil
		})

		fmt.Printf("t2: %v\n", tv)
	}()

	time.Sleep(time.Second * 2)
	fmt.Printf("last: %v\n", tvar)
}
