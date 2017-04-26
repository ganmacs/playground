package pointer

import (
	"fmt"
)

type A struct {
	value int
}

func newA1() A {
	return A{value: 0}
}

func newA2() *A {
	return &A{value: 0}
}

func c1(a A) {
	a.value = 2
}

func c2(a *A) {
	a.value = 2
}

func pMap() {
	fmt.Println("-- Pointer Map --")
	m := make(map[string]*A)

	a1 := newA1()
	a2 := newA2()

	fmt.Printf("a1=%v\n", a1)
	fmt.Printf("a2=%v\n", a2)

	m["a1"] = &a1
	m["a2"] = a2

	v1 := m["a1"]
	v2 := m["a2"]

	v1.value = 100
	v2.value = 100

	fmt.Printf("v1=%v\n", v1)
	fmt.Printf("v2=%v\n", v2)

	fmt.Printf("a1=%v\n", a1)
	fmt.Printf("a2=%v\n", a2)
}

func aMap() {
	fmt.Println("-- Actual Map --")
	m := make(map[string]A)

	a1 := newA1()
	a2 := newA2()

	fmt.Printf("a1=%v\n", a1)
	fmt.Printf("a2=%v\n", a2)

	m["a1"] = a1
	m["a2"] = *a2

	v1 := m["a1"]
	v2 := m["a2"]

	v1.value = 100
	v2.value = 100

	fmt.Printf("v1=%v\n", v1)
	fmt.Printf("v2=%v\n", v2)

	fmt.Printf("a1=%v\n", a1)
	fmt.Printf("a2=%v\n", a2)
}

func pointer1() {
	fmt.Println("-- pointer1 Map --")

	a1 := newA1()
	a2 := newA2()
	a3 := a1 // copy
	// a4 := a2
	m := make(map[A]int)

	m[a1] = 1
	m[*a2] = 2
	// fmt.Println(&a1 == a2)
	fmt.Println(&a3 == &a1)
	// fmt.Println(a4 == a2)
	// fmt.Println(*a4 == *a2)

	fmt.Println(m[a1])
	fmt.Println(m[*a2])
}

func Run() {
	a1 := newA1()
	a2 := newA2()

	fmt.Println(a1)
	fmt.Println(a2)

	c1(a1)
	c2(a2)

	fmt.Println(a1)
	fmt.Println(a2)

	pMap()
	aMap()

	pointer1()
}
