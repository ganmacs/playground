package rumor

import (
	"sync"
	"time"
)

type suspectedEntries struct {
	suspectTimer map[string]*suspectTimer
	mutex        *sync.Mutex
}

type suspectTimer struct {
	timer *time.Timer
	alive bool
	ch    chan bool
}

func newSuspectedEntries() *suspectedEntries {
	return &suspectedEntries{
		mutex:        new(sync.Mutex),
		suspectTimer: make(map[string]*suspectTimer),
	}
}

func (se *suspectedEntries) setSuspectTimer(name string, timeout time.Duration, ch chan bool) bool {
	se.mutex.Lock()
	defer se.mutex.Unlock()

	_, ok := se.suspectTimer[name]
	if ok {
		return false
	}

	timer := &suspectTimer{ch: ch, alive: false}
	timer.timer = time.AfterFunc(timeout, func() {
		se.mutex.Lock()
		timer.ch <- timer.alive
		delete(se.suspectTimer, name)
		close(timer.ch)
		se.mutex.Unlock()
	})

	se.suspectTimer[name] = timer
	return true
}

func (se *suspectedEntries) aliveState(name string) {
	se.mutex.Lock()
	defer se.mutex.Unlock()

	v, ok := se.suspectTimer[name]
	if ok {
		v.ch <- true
		v.alive = true
	}
}

func (se *suspectedEntries) get(name string) *suspectTimer {
	se.mutex.Lock()
	defer se.mutex.Unlock()

	return se.suspectTimer[name]
}
