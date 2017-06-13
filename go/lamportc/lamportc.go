package lamportc

import (
	"log"
	"sync/atomic"
)

type lclock struct {
	name string
	step uint64
}

func newClock(name string) *lclock {
	log.Printf("Create clock: %s", name)
	return &lclock{name: name}
}

func (lc *lclock) tick() {
	atomic.AddUint64(&lc.step, 1)
	log.Printf("[%s] tick %d", lc.name, lc.step)
}

func (lc *lclock) now() uint64 {
	return atomic.LoadUint64(&lc.step)
}

func (lc *lclock) set(new uint64) {
	for {
		old := lc.step
		if old >= new {
			log.Printf("[%s] %d has come, but now is %d", lc.name, new, old)
			return
		}

		if atomic.CompareAndSwapUint64(&lc.step, old, new) {
			log.Printf("[%s] Sucess change %d -> %d", lc.name, old, new+1)
			break
		}
	}
}
