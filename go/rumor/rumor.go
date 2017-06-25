package rumor

import (
	"math/rand"
	"net"
	"os"
	"strconv"
	"sync"
	"sync/atomic"
	"time"

	"github.com/ganmacs/playground/go/rumor/logger"
)

type Rumor struct {
	Name string

	// node name => node
	nodeLock    *sync.RWMutex
	Incarnation uint64

	nodeMap         map[string]*Node
	nodes           []*Node
	nodeNum         uint32
	probeIndex      int
	seqNumber       int32 // this number is used for ping
	piggybackBuffer *PiggybackBuffer

	transport  *Transport
	shutdownCh chan (int)
	config     *Config // NEED?

	logger *logger.Logger
}

func New(config *Config) (*Rumor, error) {
	ru, err := newRumor(config)
	if err != nil {
		return nil, err
	}

	ru.logger.Infof("Starting rumor... %s\n", ru.Name)

	ru.becomeAlive()

	return ru, nil
}

func newRumor(config *Config) (*Rumor, error) {
	l := config.Logger
	if l == nil {
		l = logger.NewSimpleLogger(os.Stdout)
	}

	tr := config.transport
	if tr == nil {
		trConfig := &TranportConfig{
			bindAddr: config.BindAddr,
			bindPort: config.BindPort,
			logger:   l,
		}

		dtr, err := NewTransport(trConfig)
		if err != nil {
			return nil, err
		}
		tr = dtr
	}
	tr.Start() // FIX

	ru := &Rumor{
		Name:            joinHostPort(config.BindAddr, config.BindPort),
		nodeMap:         make(map[string]*Node),
		nodeLock:        new(sync.RWMutex),
		transport:       tr,
		logger:          l,
		config:          config,
		shutdownCh:      make(chan (int), 1),
		piggybackBuffer: &PiggybackBuffer{transmitLam: config.TransmitLammda},
	}

	ru.piggybackBuffer.NodeSize = func() int {
		return ru.NumSize()
	}

	return ru, nil
}

func (ru *Rumor) Start() {
	go ru.listenPacket()
	startTick(ru.config.ProbeInterval, ru.probe)
}

func (ru *Rumor) Join(hostStr string) (int, error) {
	host, sport, err := net.SplitHostPort(hostStr)

	// lookup host name and check connection

	port, err := strconv.Atoi(sport)
	if err != nil {
		return 0, err
	}
	targetNodeName := joinHostPort(host, port)

	msg := &alive{
		Addr: targetNodeName,
		Name: targetNodeName,
	}

	ru.AliveState(msg) // register new node only

	if targetNodeName != ru.Name {
		msg = &alive{
			Name:        ru.Name,
			Addr:        ru.Name,
			Incarnation: ru.Incarnation,
		}
		if err := ru.PushMessageToBuffer(ru.Name, aliveMsg, msg); err != nil {
			return 0, err
		}
	}

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
		ru.logger.Error(err)
	}

	switch msgType {
	case pingMsg:
		ru.handlePing(packet)
	case ackMsg:
		ru.handleAck(packet)
	case compoundMsg:
		ru.handleCompound(packet)
	case aliveMsg:
		ru.handleAlive(packet)
	case pingReqMsg:
		ru.handlePingReq(packet)
	default:
		ru.logger.Errorf("Unkonow message type: %d\n", msgType)
	}
}

func (ru *Rumor) handleCompound(pack *packet) {
	bufs, err := decomposeCompoundMessage(pack.body())

	if err != nil {
		ru.logger.Fatal(err)
		return
	}

	for _, buf := range bufs {
		p := &packet{buf: buf, from: pack.from}
		ru.handlePacket(p)
	}
}

func (ru *Rumor) handleAlive(pack *packet) {
	var a alive
	if err := Decode(pack.body(), &a); err != nil {
		ru.logger.Error(err)
		return
	}

	// host, sport, err := net.SplitHostPort(a.Name)
	// port, err := strconv.Atoi(sport)
	// if err != nil {
	// 	ru.logger.Error(err)
	// 	return
	// }
	// targetNodeName := joinHostPort(host, port)
	ru.logger.Infof("Receive ALIVE messsage about %s\n", a.Name)

	ru.AliveState(&a)
}

func (ru *Rumor) handlePing(packet *packet) {
	var p ping

	if err := Decode(packet.body(), &p); err != nil {
		ru.logger.Info(err)
		return
	}

	ru.logger.Infof("Receive PING messsage and Return ACK message: %s\n", p.Name)

	ack := ack{Id: p.Id, Name: ru.Name, Addr: ru.Name}
	if err := ru.sendPackedMessage(p.Addr, ackMsg, &ack); err != nil {
		ru.logger.Info(err)
	}

	// register unkown node
	ru.nodeLock.Lock()
	nd, ok := ru.nodeMap[p.Name]

	if !ok {
		nd = &Node{
			name:      p.Name,
			addr:      p.Name,
			stateType: deadState,
		}

		ru.nodeMap[p.Name] = nd

		size := ru.NumSize()
		offset := randInt(size)
		ru.nodes = append(ru.nodes, nd)
		ru.nodes[offset], ru.nodes[size] = ru.nodes[size], ru.nodes[offset]

		atomic.AddUint32(&ru.nodeNum, 1)
	}
	ru.nodeLock.Unlock()
}

func (ru *Rumor) handlePingReq(packet *packet) {
	var p pingReq
	if err := Decode(packet.body(), &p); err != nil {
		ru.logger.Error(err)
		return
	}

	ru.logger.Infof("Recieved PING_REQ messsage from %s", p.FromName)

	addr := joinHostPort(ru.config.BindAddr, ru.config.BindPort)
	msg := ping{Id: int(ru.nextSeq()), Name: ru.Name, Addr: addr}
	ackCh := make(chan *ack)
	ru.transport.setAckHandler(msg.Id, ackCh, ru.config.ProbeTimeout)

	select {
	case <-ackCh:
		ack := ack{Id: p.Id, Name: ru.Name, Addr: ru.Name}
		if err := ru.sendPackedMessage(p.FromName, ackMsg, &ack); err != nil {
			ru.logger.Error(err)
			return
		}
		return
	case <-time.After(ru.config.ProbeTimeout):
		ru.logger.Errorf("Ack is not comming. %s is dead?\n", p.ToAddr)
	}
}

func (ru *Rumor) handleAck(packet *packet) {
	var a ack
	if err := Decode(packet.body(), &a); err != nil {
		ru.logger.Error(err)
		return
	}

	ru.logger.Infof("Recieved ACK messsage from %s", a.Name)
	if err := ru.transport.HandleAck(&a); err != nil {
		ru.logger.Error(err)
		return
	}
}

func (ru *Rumor) selectNextNode() *Node {
	tryCount := 0

START:
	if tryCount > len(ru.nodes) {
		return nil
	}
	tryCount++

	if ru.probeIndex >= len(ru.nodes) {
		ru.probeIndex = 0
	}
	node := ru.nodes[ru.probeIndex]
	ru.probeIndex++
	if node.name == ru.Name {
		goto START
	}

	if node.stateType == deadState {
		goto START
	}

	return node
}

func (ru *Rumor) probe() {
	ru.logger.Debug("Probing...")
	node := ru.selectNextNode()

	if node == nil {
		ru.logger.Debug("There is no node to send ping")
		return
	}

	addr := joinHostPort(ru.config.BindAddr, ru.config.BindPort)
	msg := ping{Id: int(ru.nextSeq()), Name: ru.Name, Addr: addr}
	ackCh := make(chan *ack)
	ru.transport.setAckHandler(msg.Id, ackCh, ru.config.ProbeTimeout*3) // three time is temporarily

	ru.logger.Infof("Send PING message to %s\n", node.Address())
	if err := ru.sendPackedMessage(node.Address(), pingMsg, &msg); err != nil {
		ru.logger.Errorf("can't send message: %s", err)
	}

	select {
	case ack, ok := <-ackCh:
		if ok {
			ru.logger.Debugf("Recieved ACK in required time: %v", ack)
			return
		} else {
			ru.logger.Error("Socket is closed")
		}
	case <-time.After(ru.config.ProbeTimeout):
		ru.logger.Errorf("In probing Ack is not comming. %s is dead?\n", node.Address())
	}

	// send ping-req
	ru.nodeLock.Lock()
	nodes := ru.selectNodes(ru.config.RumorNodeCount, func(name string, node *Node) bool {
		if node.name == ru.Name {
			return false
		}

		return node.stateType == aliveState
	})
	ru.nodeLock.Unlock()

	newMsg := &pingReq{Id: msg.Id, FromName: ru.Name, ToAddr: node.Address()}
	for _, node := range nodes {
		ru.logger.Debugf("Sending PING_REQ messaeg to %s", node.Address())
		if err := ru.sendPackedMessage(node.Address(), pingReqMsg, newMsg); err != nil {
			ru.logger.Errorf("can't send message: %s", err)
		}
	}

	select {
	case ack, ok := <-ackCh:
		if ok {
			ru.logger.Debugf("Recieved ACK by PING_REQ : %v", ack)
			return
		} else {
			ru.logger.Error("Socket is closed")
		}
	}

	ru.logger.Infof("node is dead %s", node.Address())
	node.deadNode()
}

func (ru *Rumor) nextSeq() int32 {
	return atomic.AddInt32(&ru.seqNumber, 1)
}

func (ru *Rumor) selectNodes(k int, fn func(string, *Node) bool) (nodes []*Node) {
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

func (ru *Rumor) becomeAlive() {
	aliveMsg := &alive{
		Name:        ru.Name,
		Addr:        ru.Name,
		Incarnation: ru.Tick(),
	}

	ru.AliveState(aliveMsg)
}

func (ru *Rumor) NumSize() int {
	return int(atomic.LoadUint32(&ru.nodeNum))
}

func (ru *Rumor) AliveState(a *alive) {
	ru.nodeLock.Lock()
	defer ru.nodeLock.Unlock()
	nd, ok := ru.nodeMap[a.Name]

	if !ok {
		nd = &Node{
			name:      a.Name,
			addr:      a.Addr,
			stateType: deadState,
		}
		ru.nodeMap[a.Name] = nd

		size := ru.NumSize()
		offset := randInt(size)
		ru.nodes = append(ru.nodes, nd)
		ru.nodes[offset], ru.nodes[size] = ru.nodes[size], ru.nodes[offset]

		atomic.AddUint32(&ru.nodeNum, 1)
	}

	nd.aliveNode()

	// throw away an old message
	if a.Incarnation < nd.incarnation {
		ru.logger.Debugf("Receive old ALIVE message about %s\n", a.Name)
		return
	}

	if nd.name == ru.Name {
		// declear that I'm alive or something
	} else {
		if a.Incarnation == nd.incarnation {
			return
		}

		// re-broadcast
		ru.logger.Debugf("Enqueu message for %s\n", a.Name)
		if err := ru.PushMessageToBuffer(nd.name, aliveMsg, a); err != nil {
			ru.logger.Error(err)
			return
		}

		nd.incarnation = a.Incarnation
		if nd.stateType != aliveState {
			nd.aliveNode()
		}
	}
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

func joinHostPort(host string, port int) string {
	return net.JoinHostPort(host, strconv.Itoa(port))
}

func randInt(n int) int {
	if n == 0 {
		return n
	}

	return (rand.Int() % n)
}
