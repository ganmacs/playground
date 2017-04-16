package striped

import (
	"sync"
)

type StripedDict struct {
	buckets []*bucket
}

type bucket struct {
	lock *sync.Mutex
	dict map[string]int
}

// bucketsSize is only 2^n
var bucketSize = 8

func NewStripedDict() *StripedDict {
	return &StripedDict{
		buckets: newBuckets(bucketSize),
	}
}

func (d StripedDict) Set(key string, val int) {
	bucket := d.getBucket(key)

	bucket.lock.Lock()
	bucket.set(key, val)
	bucket.lock.Unlock()
}

func (d StripedDict) Get(key string) int {
	bucket := d.getBucket(key)
	bucket.lock.Lock()
	defer bucket.lock.Unlock()

	return bucket.get(key)
}

func newBuckets(bucketSize int) []*bucket {
	buckets := make([]*bucket, bucketSize)

	for i := 0; i < bucketSize; i++ {
		buckets[i] = &bucket{
			lock: new(sync.Mutex),
			dict: make(map[string]int),
		}
	}

	return buckets
}

func (d StripedDict) getBucket(key string) *bucket {
	hashedKey := fnvPrime(key)

	i := uint((bucketSize - 1)) & hashedKey
	return d.buckets[i]
}

func (b *bucket) get(key string) int {
	return b.dict[key]
}

func (b *bucket) set(key string, val int) {
	b.dict[key] = val
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
