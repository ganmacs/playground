package patt

import (
	"fmt"
)

type SomeBehivor interface {
	DoSomehting(arg string) string
}

type K struct {
}

func (k *K) DoSomehting(arg string) string {
	fmt.Println(arg)
	return arg
}

func NewK() *K {
	return &K{}
}

func AAA() {
	var behivor SomeBehivor
	behivor = NewK()
	behivor.DoSomehting("fff")
}
