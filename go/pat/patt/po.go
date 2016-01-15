package patt

import (
	"fmt"
)

type SomeBehivorA interface {
	DoSomething() string
}

type DStruct struct {
	Name string
}

func (s *DStruct) DoSomething() string {
	return s.Name
}

type StructK struct {
	*DStruct
}

func BBB() {
	b := &StructK{&DStruct{"name"}}
	name := b.DoSomething()
	fmt.Println(name)
}
