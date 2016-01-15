package patt

import (
	"fmt"
)

type singleton struct {
}

var instance *singleton

func (i *singleton) Good() {
	fmt.Println("sss")
}

func GetInstane() *singleton {
	if instance == nil {
		instance = &singleton{}
	}
	return instance
}
