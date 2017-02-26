package main

import (
	"github.com/cenkalti/backoff"

	"errors"
	"fmt"
	"math"
	"math/rand"
	"time"
)

type Boff struct {
	Clock           Clock
	currentInterval time.Duration
	startTime       time.Time
	maxInterval     time.Duration
	timeout         time.Duration
}

type Clock interface {
	Now() time.Time
}

const (
	Stop               = -1
	DefaultMaxInterval = 60 * time.Second
	DefaultTimeout     = 10 * time.Minute
	InitialInterval    = 500 * time.Millisecond
)

type sClock struct{}

func (t sClock) Now() time.Time {
	return time.Now()
}

var systemClock = sClock{}

func NewBoff() *Boff {
	b := &Boff{
		Clock:           systemClock,
		maxInterval:     DefaultMaxInterval,
		timeout:         DefaultTimeout,
		currentInterval: InitialInterval,
	}
	b.Reset()
	return b
}

func (b *Boff) Reset() {
	b.currentInterval = InitialInterval
	b.startTime = b.Clock.Now()
}

func (b *Boff) GetElapsedTime() time.Duration {
	return b.Clock.Now().Sub(b.startTime)
}

func (b *Boff) NextBackOff() time.Duration {
	if b.GetElapsedTime() > b.timeout {
		return Stop
	}

	currentInterval := math.Min(float64(b.currentInterval*2), float64(b.maxInterval))
	b.currentInterval = time.Duration(currentInterval)

	return time.Duration(currentInterval * rand.Float64())
}

type Operation func() error

func Retry(o Operation) error {
	b := NewBoff()
	var next time.Duration
	var err error

	for {
		if err = o(); err == nil {
			return nil
		}

		next = b.NextBackOff()
		if next == Stop {
			return err
		}

		time.Sleep(next)
	}
}

func main() {
	t0()
	t1()
	t2()
}

func t2() {
	fmt.Println("--t2--")
	b := NewBoff()

	fmt.Println(Stop)
	fmt.Println(b.NextBackOff())
	fmt.Println(b.NextBackOff())
	fmt.Println(b.NextBackOff())
	fmt.Println(b.NextBackOff())

	b.Reset()

	fmt.Println(b.NextBackOff())
	fmt.Println(b.NextBackOff())
	fmt.Println(b.NextBackOff())

	Retry(func() error {
		fmt.Println("retry")
		return errors.New("foo")
	})
}

func t1() {
	fmt.Println(500 * time.Millisecond)
	fmt.Println(500 * time.Second)
	fmt.Println(500 * time.Minute)
}

func t0() {
	fmt.Println("hgoe")
	bo := backoff.NewExponentialBackOff()

	fmt.Println(bo.NextBackOff())
	fmt.Println(bo.NextBackOff())
	bo.Reset()
	fmt.Println(bo.NextBackOff())
}
