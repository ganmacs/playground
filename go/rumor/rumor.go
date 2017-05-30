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

	transport  *Transport
	shutdownCh chan (int)
	config     *Config // NEED?

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
		config:     config,
		shutdownCh: make(chan (int), 1),
	}

	return ru, nil
}

func (ru *Rumor) Start() {
}

func (ru *Rumor) Join(ip string) (int, error) {
	return 0, nil
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
	aliveMsg := &alive{
		nodeName: ru.config.Name,
		port:     ru.config.BindPort,
		addr:     ru.config.BindAddr,
	}

	return ru.setAliveState(aliveMsg)
}

func (ru *Rumor) setAliveState(a *alive) error {
	ru.nodeLock.Lock()
	defer ru.nodeLock.Unlock()
	nd, ok := ru.nodeMap[ru.Name]

	if !ok {
		nd = &node{
			addr:      a.addr,
			port:      a.port,
			stateType: deadState,
		}
	}

	ru.nodes = append(ru.nodes, nd)
	ru.nodeNum += 1

	nd.AliveState()

	return nil
}
