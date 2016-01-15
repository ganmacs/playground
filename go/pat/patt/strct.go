package patt

import (
	"fmt"
)

func (d *D) someInitialize() {
	// some
}

func (d *D) P() {
	fmt.Print("ss\n")
}

// D is a type
type D struct {
	Name string
}

// NewStructD is a constructor
func NewStructD(name string) *D {
	d := &D{Name: name}
	d.someInitialize()
	return d
}
