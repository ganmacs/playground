package rumor

import (
	"log"
	"os"
	"sync"
	"sync/atomic"
	"time"
)

type Rumor struct {
	Name string

	// node name => node
	nodeLock   *sync.RWMutex
	nodeMap    map[string]*node
	nodes      []*node
	nodeNum    int
	probeIndex int
	seqNumber  int32 // this number is used for ping

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
		trConfig := &TranportConfig{
			bindAddr: config.BindAddr,
			bindPort: config.BindPort,
			logger:   logger,
		}

		dtr, err := NewTransport(trConfig)
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
	go ru.listenPacket()
	startTick(ru.config.ProbeInterval, ru.probe)
}

func (ru *Rumor) Join(ip string) (int, error) {
	return 0, nil
}

// Listen port by udp
func (ru *Rumor) listenPacket() {
	for {
		select {
		case packet := <-ru.transport.PacketCh():
			go ru.handlePacket(packet)
		case <-ru.shutdownCh:
			return
		}
	}
}

func (ru *Rumor) handlePacket(packet *packet) {
	msgType, err := packet.messageType()
	if err != nil {
		ru.logger.Fatalln(err)
	}

	switch msgType {
	case pingMsg:
		ru.handlePing(packet)
	default:
		ru.logger.Printf("Unkonow message type: %d\n", msgType)
	}
}

func (ru *Rumor) handlePing(packet *packet) {
	ru.logger.Println("Handling Ping messsage...")
	var p ping

	if err := Decode(packet.body(), &p); err != nil {
		ru.logger.Println(err)
		return
	} else {
		ru.logger.Printf("ping form %s\n", p.name)
	}

	ack := ack{id: p.id, name: ru.config.Name}

	ru.logger.Printf("Sendign ack to %s", p.name)
	if err := ru.transport.sendPackedMessage(packet.from.String(), ackMsg, &ack); err != nil {
		ru.logger.Println(err)
	}
}

func (ru *Rumor) selectNextNode() *node {
	tryCount := 0

START:
	if tryCount > len(ru.nodes) {
		return nil
	}
	tryCount++

	if ru.probeIndex > len(ru.nodes) {
		ru.probeIndex = 0
	}
	node := ru.nodes[ru.probeIndex]

	if node.name == ru.config.Name {
		goto START
	}

	ru.probeIndex++

	return node
}

func (ru *Rumor) probe() {
	ru.logger.Println("probing...")
	node := ru.selectNextNode()

	if node == nil {
		ru.logger.Println("There is no node to send ping")
		return
	}

	msg := ping{id: int(ru.nextSeq()), name: node.name}
	ackCh := make(chan *ack)
	ru.transport.setAckHandler(msg.id, ackCh)

	if err := ru.transport.sendPackedMessage(node.Address(), pingMsg, &msg); err != nil {
		ru.logger.Printf("can't send message: %s", err)
	}

	select {
	case ack := <-ackCh:
		ru.logger.Printf("Recieved ack: %v", ack)
	case <-time.After(ru.config.ProbeTimeout):
		ru.logger.Println("node is dead?")
	}
}

func (ru *Rumor) nextSeq() int32 {
	return atomic.AddInt32(&ru.seqNumber, 1)
}

func (ru *Rumor) selectNodes(k int, fn func(string, *node) bool) (nodes []*node) {
	v := 0
	for name, node := range ru.nodeMap {
		if fn(name, node) {
			v += 1
			nodes = append(nodes, node)
		}

		if v >= k {
			return
		}
	}
	return
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
			name:      a.nodeName,
		}
	}

	ru.nodes = append(ru.nodes, nd)
	ru.nodeNum += 1

	nd.AliveState()

	return nil
}

func startTick(t time.Duration, fn func()) {
	c := time.Tick(t * time.Second)
	go func() {
		for {
			<-c // block until next tick time
			go fn()
		}
	}()
}
