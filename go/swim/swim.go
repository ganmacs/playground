package swim

import (
	"bufio"
	"bytes"
	"fmt"
	"log"
	"net"
	"os"
	"time"
)

type msgType int8

const (
	pingMsg msgType = iota
	pongMsg
)

const (
	ADDR = "127.0.0.1:3333"
)

type Swim struct {
	transport Transport
	logger    *log.Logger
}

func NewSwim(name string) *Swim {
	prefix := fmt.Sprintf("[swim] %s ", name)
	return &Swim{
		transport: *NewTransport(),
		logger:    log.New(os.Stdout, prefix, log.LstdFlags),
	}
}
func (sw *Swim) listenStream() {
	for {
		select {
		case conn := <-sw.transport.streamCh:
			go sw.handleConn(conn)
			// should listen shutdow channel
		}
	}
}

func (sw *Swim) handleConn(conn net.Conn) {
	defer conn.Close()

	sw.logger.Printf("Stream connection %s", conn.RemoteAddr())

	if err := conn.SetReadDeadline(time.Now().Add(10 * time.Second)); err != nil {
		fmt.Println(err)
		panic(1)
	}

	msgType, _, err := sw.readStream(conn)
	if err != nil {
		fmt.Println(err)
		panic(1)
	}
	switch msgType {
	case pingMsg:
		sw.logger.Println("ping")
		sw.sendPong(conn)
	case pongMsg:
		sw.logger.Println("pong")
	}
}

func (sw *Swim) readStream(conn net.Conn) (msgType, *bufio.Reader, error) {
	bufConn := bufio.NewReader(conn) // cast io.Reader?

	msgType, err := sw.readMsgType(bufConn)

	return msgType, bufConn, err
}

func (sw *Swim) pingAndWaitForPong() {
	dialer := net.Dialer{Timeout: time.Second * 2}
	conn, err := dialer.Dial("tcp", ADDR)

	if err != nil {
		sw.logger.Fatalf("connection failed: %s", err)
		return
	}
	defer conn.Close()

	sw.sendPing(conn)

	msgType, _, err := sw.readStream(conn)
	if err != nil {
		sw.logger.Fatalf("pong doesn't recive: %s", err)
		return
	}

	if msgType == pongMsg {
		sw.logger.Println("pong!!!")
	}
}

func (sw *Swim) sendPing(conn net.Conn) {
	sw.logger.Printf("send ping to %s", conn.RemoteAddr())

	buff := composeMsg(pingMsg)
	if err := sw.sendMsgToStream(conn, buff.Bytes()); err != nil {
		sw.logger.Fatalf("sending ping is failed: %s", err)
	}
}

func (sw *Swim) sendPong(conn net.Conn) {
	sw.logger.Printf("send pong to %s", conn.RemoteAddr())

	buff := composeMsg(pongMsg)
	if err := sw.sendMsgToStream(conn, buff.Bytes()); err != nil {
		sw.logger.Fatalf("sending pong is failed: %s", err)
	}
}

func (sw *Swim) sendMsgToStream(conn net.Conn, buff []byte) error {
	n, err := conn.Write(buff)
	if err != nil {
		return err
	}

	sw.logger.Printf("writing %d bytes", n)
	return nil
}

func (sw *Swim) schedule() {
	t := time.NewTicker(1 * time.Second)

	go func(c <-chan time.Time) {
		for {
			select {
			case <-c:
				sw.pingAndWaitForPong()
				// case <-stop:
				// return
			}
		}
	}(t.C)
}

func (sw *Swim) readMsgType(connBuff *bufio.Reader) (msgType, error) {
	buf := [1]byte{0}
	if _, err := connBuff.Read(buf[:]); err != nil {
		return 0, err
	}

	return msgType(buf[0]), nil
}

func (sw *Swim) Run() {
	go sw.listenStream()
	go sw.schedule()

	time.Sleep(1000 * time.Second)
}

func composeMsg(mt msgType) *bytes.Buffer {
	buf := bytes.NewBuffer(nil)
	buf.WriteByte(uint8(mt))
	return buf
}

func Run() {
	swim := NewSwim("server 1")
	swim.Run()
}
