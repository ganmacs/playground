package main

import (
	"fmt"
	"io"
	"os"
)

type Looper struct {
	No int
}

func NewLooper(i int) *Looper {
	return &Looper{No: i}
}

func (l *Looper) Scan() bool {
	l.No--
	return l.No > 0
}

type Readr struct {
	buf []byte
}

func (r *Readr) Read(p []byte) (n int, err error) {
	return 1, os.ErrNotExist
}

func NewReadrSize(rd io.Reader, size int) *Readr {
	b, ok := rd.(*Readr)
	if !ok {
		panic("panic")
	}
	return b
}

func NewReadr(rd io.Reader, size int) *Readr {
	return NewReadrSize(rd, size)
}

type MyScanner struct {
	r     io.Reader
	start int
	end   int
	buf   []byte
	token []byte
	err   error
}

func newMyScanner(r io.Reader) *MyScanner {
	return &MyScanner{
		r:   r,
		buf: make([]byte, 4096),
	}
}

func (s *MyScanner) SetErr(e error) {
	if s.err == nil {
		s.err = e
	}
}

func (s *MyScanner) Read(buf []byte) {
	if s.end > s.start || s.err != nil {
		fmt.Println("fff")
	}
	// n, err := s.r.Read(buf[s.end:len(s.buf)])
	// s.end += n
	// if err != nil {
	// 	s.SetErr(err)
	// }
}

func (s *MyScanner) Scan() bool {
	if s.end > s.start || s.err != nil {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}

	// s.Read(s.buf)
	return true
}

func (s *MyScanner) Text() string {
	return string(s.token)
}

func main() {
	fp, err := os.Open("main.go")
	if err != nil {
		panic(err)
	}

	defer fp.Close()

	a := make([]int, 50)
	a[1] = 10

	looper := NewLooper(10)
	for looper.Scan() {
		fmt.Println(looper.No)
	}

	scanner := newMyScanner(fp)

	// for scanner.Scan() {
	if scanner.Scan() {
		fmt.Println("Success")
	}

	// fmt.Println(scanner.err)
	// fmt.Println(scanner.start)
	// fmt.Println(scanner.end > scanner.start)

	// fmt.Println(a)
	// fmt.Println(len(scanner.buf))
	// fmt.Println(fp)
	// NewReadrSize()
	// a := 100
	// r, err := interface{}(a).(int)
	// fmt.Println(r)
	// fmt.Println(err)
	// fmt.Println(bufio.MaxScanTokenSize)
}
