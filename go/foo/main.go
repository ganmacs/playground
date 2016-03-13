package main

type Matchable interface {
	Match() bool
}

type Repository struct {
	Matchable
}

func (r Repository) Match() bool {
	return true
}

type RepoChan chan *Repository

type MatchableChan chan Matchable

func (m MatchableChan) collect() MatchableChan {
	f := make(MatchableChan)

	go func() {
		for k := range m {
			if k.Match() {
				f <- k
			}
		}
		close(m)
	}()

	return f
}

func (r RepoChan) Match() bool {
}

func foo() {
	var v2 Matchable
	v2 = make(RepoChan)
	// v2 = Repository{}

	// var v MatchableChan
	// v <- v2
	// v.collect()
}

func main() {
	c := make(chan int)
	for i := 0; i < 10; i++ {
		c1 = newChan()
	}
}

func newChan() chan int {
	c := make(chan int)
	c <- 1
	c <- 2
	c <- 3
	return c
}
