package rumor

import (
	"errors"
	"fmt"
	"net"

	"github.com/ganmacs/playground/go/rumor/logger"
)

const (
	udpPacketBufSize = 2048
)

type ackHandler struct {
	ch chan *ack
}

type Transport struct {
	packetCh chan *packet

	udpListener *net.UDPConn

	shutdownCh chan int

	ackHandlers map[int]*ackHandler

	logger *logger.Logger
}

type TranportConfig struct {
	bindAddr string
	bindPort int
	logger   *logger.Logger
}

func NewTransport(config *TranportConfig) (*Transport, error) {
	tr := &Transport{
		packetCh:    make(chan (*packet)),
		shutdownCh:  make(chan (int)),
		ackHandlers: make(map[int]*ackHandler),
		logger:      config.logger,
	}

	addr := config.bindAddr
	ip := net.ParseIP(addr)

	if err := tr.setupUDP(ip, config.bindPort); err != nil {
		tr.logger.Error(err)
	}

	return tr, nil
}

func (tr *Transport) Start() {
	go tr.listenUDP()
}

func (tr *Transport) setupUDP(ip net.IP, port int) error {
	udpAddr := &net.UDPAddr{IP: ip, Port: port}
	udpLn, err := net.ListenUDP("udp", udpAddr)
	if err != nil {
		tr.logger.Error(err)
		return err
	}

	tr.udpListener = udpLn
	return nil
}

func (tr *Transport) listenUDP() {
	for {
		buf := make([]byte, udpPacketBufSize)

		n, addr, err := tr.udpListener.ReadFromUDP(buf)
		if err != nil {
			tr.logger.Error("could not read %v", err)
			continue
		}

		tr.packetCh <- &packet{buf: buf[:n], from: addr}
	}
}

func (tr *Transport) PacketCh() chan (*packet) {
	return tr.packetCh
}

func (tr *Transport) setAckHandler(seqNo int, ch chan *ack) {
	tr.ackHandlers[seqNo] = &ackHandler{ch}
}

func (tr *Transport) deleteAckHandler(seqNo int) {
	delete(tr.ackHandlers, seqNo)
}

func (tr *Transport) HandleAck(ackMsg *ack) error {
	handler, ok := tr.ackHandlers[ackMsg.Id]
	if !ok {
		return errors.New(fmt.Sprintf("unknow ack message id %v", ackMsg))
	}
	tr.deleteAckHandler(ackMsg.Id)

	handler.ch <- ackMsg
	return nil
}

func (tr *Transport) sendPackedMessage(addr string, msgType messageType, msg interface{}) error {
	emsg, err := Encode(msgType, msg)
	if err != nil {
		return err
	}

	return tr.sendData(addr, emsg.Bytes())
}

func (tr *Transport) sendMessage(addr string, msg []byte) error {
	return tr.sendData(addr, msg)
}

// for sending message without piggyback
func (tr *Transport) sendCompoundMessage(addr string, msgs [][]byte) error {
	buf := ComposeCompoundMessage(msgs)
	if err := tr.sendData(addr, buf.Bytes()); err != nil {
		return err
	}

	return nil
}

func (tr *Transport) sendData(addr string, data []byte) error {
	conn, err := net.Dial("udp", addr)
	if err != nil {
		return err
	}

	size, err := conn.Write(data)
	if err != nil {
		return err
	}

	if len(data) != size {
		tr.logger.Errorf("failed writing data %d/%d\n", size, len(data))
		// return error object
	}

	tr.logger.Debugf("Sucess sending data %d bytes\n", size)

	return nil
}

// send packet with piggyback message
func (ru *Rumor) sendPackedMessage(addr string, msgType messageType, msg interface{}) error {
	emsg, err := Encode(msgType, msg)
	if err != nil {
		return err
	}

	bmsg := emsg.Bytes()

	msgs := ru.GetPiggybackData(len(bmsg), compoundMsgSizeOverhead)

	if len(msgs) == 0 {
		return ru.transport.sendMessage(addr, bmsg)
	}

	return ru.transport.sendCompoundMessage(addr, append(msgs, bmsg))
}
