package pool

import (
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"time"
)

var (
	MaxWorker = os.Getenv("MAX_WORKERS")
	MaxQueue  = os.Getenv("MAX_QUEUE")
)

type Job struct {
	value string // tmp
}

type Worker struct {
	WorkerPool chan chan Job
	JobChannel chan Job
	Stop       chan bool
}

type WorkerPool struct {
	WorkerPool  chan chan Job
	LimitNumber int
}

func NewWorkerPool(count int, fn func(job Job)) *WorkerPool {
	pool := make(chan chan Job, count)
	return &WorkerPool{
		WorkerPool:  pool,
		LimitNumber: count,
	}
}

func (wp *WorkerPool) Run() {
	for i := 0; i < wp.LimitNumber; i++ {
		worker := NewWorker(wp.WorkerPool)
		worker.Start()
	}
}

func (wp *WorkerPool) Handle(job Job) {
	worker := <-wp.WorkerPool
	worker <- job
}

func NewWorker(pool chan chan Job) Worker {
	return Worker{
		WorkerPool: pool,
		JobChannel: make(chan Job),
		Stop:       make(chan bool),
	}
}

func (w *Worker) Start() {
	go func() {
		for {
			w.WorkerPool <- w.JobChannel

			select {
			case job := <-w.JobChannel:
				log.Printf("[Start] processing {%s} \n", job.value)
				for i := 0; i <= rand.Intn(10000000000000); i++ {
					// something heavy job
				}
				log.Printf("[Finish] processing {%s}\n", job.value)
			case <-w.Stop:
				return
			}
		}
	}()
}

type Server interface {
	Run()
	handle()
}

type Client interface {
	Call()
}

type ChanServer struct {
	queue      chan Job
	workerPool WorkerPool
}

type ChanClient struct {
	queue chan Job
}

func NewServerWithChan(q chan Job) (Server, error) {
	defaultMaxWorker := 5

	if MaxWorker != "" {
		v, err := strconv.Atoi(MaxWorker)
		if err != nil {
			return nil, err
		}
		defaultMaxWorker = v
	}

	wp := NewWorkerPool(defaultMaxWorker, func(j Job) {
		log.Panicln(j)
	})

	return &ChanServer{
		queue:      q,
		workerPool: *wp,
	}, nil
}

func NewChanClient(q chan Job) *ChanClient {
	return &ChanClient{queue: q}
}

func (serv *ChanServer) Run() {
	serv.workerPool.Run()
	go serv.handle()
}

func (serv *ChanServer) handle() {
	for {
		select {
		case j := <-serv.queue:
			go func(j Job) {
				serv.workerPool.Handle(j)
			}(j)
		}
	}
}

func (serv *ChanClient) Call(s string) {
	log.Printf("[Enqueued] {%v}\n", s)
	serv.queue <- Job{s}
}

func Run() {
	defaultMaxQueue := 30
	if MaxQueue != "" {
		v, err := strconv.Atoi(MaxQueue)
		if err != nil {
			log.Fatal(err)
			os.Exit(1)
		}
		defaultMaxQueue = v
	}

	queue := make(chan Job, defaultMaxQueue)

	server, err := NewServerWithChan(queue)
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}
	server.Run()

	client := NewChanClient(queue)

	for i := 0; i < 100; i++ {
		v := fmt.Sprintf("Invokeing : %d", i)
		client.Call(v)
	}

	time.Sleep(1000 * time.Second)
}
