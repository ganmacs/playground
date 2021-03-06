package pool2

import (
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"sync"
	"time"
)

var (
	MaxWorker = os.Getenv("MAX_WORKERS")
	MaxQueue  = os.Getenv("MAX_QUEUE")
)

type Job struct {
	value string // tmp
}

type Server interface {
	Start()
	Stop()
}

type Client interface {
	Call(Job)
}

type ChanServer struct {
	queue      chan Job
	MaxWorkers int
	wg         sync.WaitGroup
}

type ChanClient struct {
	queue chan Job
}

func NewServerWithChan(que chan Job) (Server, error) {
	defaultMaxWorker, err := parseOrDefault(MaxWorker, 5)
	if err != nil {
		return nil, err
	}

	return &ChanServer{
		queue:      que,
		MaxWorkers: defaultMaxWorker,
	}, nil
}

func NewChanClient(q chan Job) Client {
	return &ChanClient{queue: q}
}

func (serv *ChanServer) Start() {
	for i := 0; i < serv.MaxWorkers; i++ {
		serv.wg.Add(1)

		go func() {
			defer serv.wg.Done()

			for job := range serv.queue {
				log.Printf("[Start] processing {%s} \n", job.value)
				// something heavy job
				for i := 0; i <= rand.Intn(10000000000000); i++ {
				}
				log.Printf("[Finish] processing {%s}\n", job.value)
			}
		}()
	}
}

func (serv *ChanServer) Stop() {
	close(serv.queue)
	serv.wg.Wait()
}

func (c *ChanClient) Call(job Job) {
	log.Printf("[Enqueued] {%v}\n", job.value)
	c.queue <- job
}

func Run() {
	defaultMaxQueue, err := parseOrDefault(MaxQueue, 30)
	if err != nil {
		log.Fatal(err)
		os.Exit(1)
	}

	queue := make(chan Job, defaultMaxQueue)

	server, err := NewServerWithChan(queue)
	if err != nil {
		log.Fatalln(err)
		os.Exit(1)
	}
	server.Start()

	client := NewChanClient(queue)

	for i := 0; i < 100; i++ {
		v := fmt.Sprintf("Invokeing : %d", i)
		client.Call(Job{v})
	}

	time.Sleep(1000 * time.Second)
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
