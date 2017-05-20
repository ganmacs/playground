package rumor

import (
	"log"
	"os"
	"sync"
)

type Rumor struct {
	Name string

	// node name => node
	nodeLock *sync.RWMutex
	nodeMap  map[string]*node
	nodes    []*node
	nodeNum  int

	transport  Transport
	shutdownCh chan (int)

	logger *log.Logger
}

func New(config *Config) (*Rumor, error) {
	ru, err := newRumor(config)
	if err != nil {
		return nil, err
	}

	ru.logger.Printf("Starting rumor... %s\n", ru.Name)

	if err := ru.becomeAlive(); err != nil {
		return nil, err
	}
	return ru, nil
}

func newRumor(config *Config) (*Rumor, error) {
	logger := log.New(os.Stdout, "[Rumor] ", log.LstdFlags)

	tr := config.transport
	if tr == nil {
		trConfig := &DefautTranportConfig{
			bindAddr: config.BindAddr,
			bindPort: config.BindPort,
			logger:   logger,
		}

		dtr, err := NewDefaultTransport(trConfig)
		if err != nil {
			logger.Println(err)
			return nil, err
		}
		tr = dtr
	}
	tr.Start() // FIX

	ru := &Rumor{
		Name:       config.Name,
		nodeMap:    make(map[string]*node),
		nodeLock:   new(sync.RWMutex),
		transport:  tr,
		logger:     logger,
		shutdownCh: make(chan (int), 1),
	}

	go ru.listenStream()
	go ru.listenPacket()
	// scheduling sending mesage?

	return ru, nil
}

func (ru *Rumor) Join(addr string) (int, error) {
	for {
	}
	return ru.nodeNum, nil
}

// Listen port by tcp
func (ru *Rumor) listenStream() {
	select {
	case conn := <-ru.transport.StreamCh():
		go ru.handleStream(conn)
	case <-ru.shutdownCh:
		return
	}
}

func (ru *Rumor) handleStream(stream *stream) {
	ru.logger.Printf("Established connection from %s", stream.conn.RemoteAddr())

	msgType, err := readMsgType(stream)
	if err != nil {
		ru.logger.Println(err)
		return
	}

	switch msgType {
	case pingMsg:
		ru.logger.Println("Recived pingMsg")
		return
	case aliveMsg:
		ru.logger.Println("Recived aliveMsg")
		return
	}
}

// Listen port by udp
func (ru *Rumor) listenPacket() {
	select {
	case packet := <-ru.transport.PacketCh():
		go ru.handlePacket(packet)
	case <-ru.shutdownCh:
		return
	}
}

func (ru *Rumor) handlePacket(packet *packet) {
}

func (ru *Rumor) becomeAlive() error {
	ru.nodeLock.Lock()
	defer ru.nodeLock.Unlock()
	// node, ok := ru.nodeMap[ru.Name]

	// if !ok {
	// return nil
	// }

	return nil
}
