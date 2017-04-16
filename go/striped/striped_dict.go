package striped

import (
	"sync"
)

type StripedDict struct {
	stripes []*stripe
	dict    map[string]int
}

type stripe struct {
	lock *sync.Mutex
}

var stripedSize = 8

func NewStripedDict() *StripedDict {
	return &StripedDict{
		stripes: newStripes(stripedSize),
		dict:    make(map[string]int),
	}
}

func (d StripedDict) Set(key string, val int) {
	stripe := d.getStripe(key)
	stripe.lock.Lock()

	d.dict[key] = val

	stripe.lock.Unlock()
}

func (d StripedDict) Get(key string) int {
	stripe := d.getStripe(key)
	stripe.lock.Lock()
	defer stripe.lock.Unlock()

	return d.dict[key]
}

func newStripes(stripeSize int) []*stripe {
	stripes := make([]*stripe, stripeSize)

	for i := 0; i < stripeSize; i++ {
		stripes[i] = &stripe{
			lock: new(sync.Mutex),
		}
	}

	return stripes
}

func (d StripedDict) getStripe(key string) *stripe {
	hashedKey := fnvPrime(key)

	// only use for a power of 2 - 1
	i := uint((stripedSize - 1)) & hashedKey
	return d.stripes[i]
}

// fnv hash function
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV_prime
func fnvPrime(s string) uint {
	var hash uint = 2166136261

	for _, c := range s {
		hash *= 16777619
		hash ^= uint(c)
	}

	return hash
}
