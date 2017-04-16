package striped

import "sync"

type SynchronizedDict struct {
	lock *sync.Mutex
	dict map[string]int
}

func NewSynchronizedDict() *SynchronizedDict {
	return &SynchronizedDict{
		lock: new(sync.Mutex),
		dict: make(map[string]int),
	}
}

func (d SynchronizedDict) Set(key string, val int) {
	d.lock.Lock()
	d.dict[key] = val
	d.lock.Unlock()
}

func (d SynchronizedDict) Get(key string) int {
	d.lock.Lock()
	defer d.lock.Unlock()

	return d.dict[key]
}
