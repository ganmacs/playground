package lock

import (
	"sync"
)

func Run2() {
	v := 1
	m := new(sync.Mutex)

	go func() {
		m.Lock()
		v += 1
		m.Unlock()
	}()

	go func() {
		m.Lock()
		v += 1
		m.Unlock()
	}()
}
