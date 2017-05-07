package dpool

import (
	"log"
	"os"
	"sync/atomic"
)

type process func(int)

type Dpool struct {
	queue       chan int
	sem         chan int
	shutdown    chan int
	step        uint32
	processSize uint32
	queueSize   uint32
	process     process
	logger      *log.Logger
}

func NewDPool(queueSize, processSize int, process process) *Dpool {
	dp := &Dpool{
		step:        uint32(processSize - 1),
		process:     process,
		processSize: uint32(processSize),
		queueSize:   uint32(queueSize),
		queue:       make(chan int, queueSize),
		sem:         make(chan int, processSize),
		shutdown:    make(chan int),
		logger:      log.New(os.Stdout, "[dynamic pool]", log.LstdFlags),
	}

	for i := 0; i < processSize; i++ {
		go dp.startConsumer(i)
	}

	return dp
}

func (dp *Dpool) startConsumer(i int) {
	dp.logger.Printf("start consumer %d", i)

	for {
		select {
		case v := <-dp.queue:
			dp.logger.Printf("start processing in consumer %d: %d", i, v)
			dp.process(v)
			dp.logger.Printf("finish processing in consumer %d: %d", i, v)
		case <-dp.shutdown:
			dp.logger.Printf("Shuting down consumer %d", i)
			return
		}
	}
}

func (dp *Dpool) Post(v int) {
	dp.logger.Printf("queued: %d", v)
	dp.queue <- v
}

func (dp *Dpool) incPoolSize() error {
	return nil
}

func (dp *Dpool) DecProcess() error {
	atomic.AddUint32(&dp.processSize, ^uint32(0)) // subtract 1
	dp.shutdown <- 1

	return nil
}

func (dp *Dpool) IncProcess() error {
	s := atomic.AddUint32(&dp.step, 1)
	go dp.startConsumer(int(s))

	return nil
}
