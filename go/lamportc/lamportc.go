package lamportc

import (
	"log"
	"sync/atomic"
)

type lclock struct {
	step uint64
}

func newClock() *lclock {
	return &lclock{}
}

func (lc *lclock) tick() {
	atomic.AddUint64(&lc.step, 1)
}

func (lc *lclock) set(new uint64) {
	for {
		old := lc.step
		if old > new {
			log.Printf("%d has come, but now is %d", new, old)
			return
		}

		if atomic.CompareAndSwapUint64(&lc.step, old, new) {
			return
		}
	}
}
