package main

import (
	"fmt"
	"github.com/ganmacs/playground/go/istm/istm"
)

func main() {
	tvar := istm.NewTVar(10)

	go func() {
		istm.Atomically(func(t *istm.Txn) (*istm.TVar, error) {
			v := tvar.Read(t)
			tvar.Write(t, v+1)
			return tvar, nil
		})

		fmt.Println(v)
	}()

	go func() {
		istm.Atomically(func(t *istm.Txn) (*istm.TVar, error) {

			return tvar, nil
		})
	}()
}
