package pool3

import (
	"log"
	"math/rand"
	"os"
	"strconv"
	"sync"
)

var (
	MaxWorker = os.Getenv("MAX_WORKERS")
	MaxQueue  = os.Getenv("MAX_QUEUE")
)

type Future chan *Response

func (c *Future) Get() int {
	select {
	case v := <-*c:
		return v.value
	}
}

type Request struct {
	job  Job
	resp Future
}

type Job struct {
	value int // tmp
}

type Response struct {
	value int
}

type Server interface {
	Start()
	Stop()
}

type Client interface {
	Call(Job) int
	Enqueue(Job) Future
}

type ChanServer struct {
	queue      chan *Request
	MaxWorkers int
	wg         sync.WaitGroup
}

type ChanClient struct {
	queue chan *Request
}

func NewServerWithChan(que chan *Request) (Server, error) {
	defaultMaxWorker, err := parseOrDefault(MaxWorker, 5)
	if err != nil {
		return nil, err
	}

	return &ChanServer{
		queue:      que,
		MaxWorkers: defaultMaxWorker,
	}, nil
}

func NewChanClient(q chan *Request) Client {
	return &ChanClient{queue: q}
}

func (serv *ChanServer) Start() {
	for i := 0; i < serv.MaxWorkers; i++ {
		go serv.RunWorker()
	}
}

func (serv *ChanServer) RunWorker() {
	serv.wg.Add(1)
	defer serv.wg.Done()

	for req := range serv.queue {
		log.Printf("[Start] processing No. %d\n", req.job.value)

		v := 0
		for i := 0; i <= rand.Intn(10000000000000); i++ {
			v += i
		}
		req.resp <- &Response{v}
		log.Printf("[Finish] processing No. %d\n", req.job.value)
	}
}

func (serv *ChanServer) Stop() {
	close(serv.queue)
	serv.wg.Wait()
}

func (c *ChanClient) Call(job Job) int {
	f := c.Enqueue(job)
	return f.Get()
}

func (c *ChanClient) Enqueue(job Job) Future {
	f := make(Future)
	req := &Request{
		job:  job,
		resp: f,
	}
	c.queue <- req
	log.Printf("[Enqueued] No. {%v}\n", job.value)

	return f
}

func Run() {
	defaultMaxQueue, err := parseOrDefault(MaxQueue, 30)
	if err != nil {
		log.Fatal(err)
		os.Exit(1)
	}
	queue := make(chan *Request, defaultMaxQueue)

	// start server
	server, err := NewServerWithChan(queue)
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}
	server.Start()

	// start client
	client := NewChanClient(queue)
	var wg sync.WaitGroup
	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			f := client.Enqueue(Job{i})
			log.Printf("[Recieved] No. %d, Value = %v", i, f.Get())
		}(i)
	}

	wg.Wait()
}

func parseOrDefault(s string, defVal int) (int, error) {
	if s != "" {
		v, err := strconv.Atoi(MaxQueue)
		if err != nil {
			return 0, err
		}
		return v, nil
	}
	return defVal, nil
}
