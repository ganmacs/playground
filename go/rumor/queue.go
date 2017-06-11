package rumor

import (
	"errors"
	"sync"
)

type Messages []*PackedMessage

type PackedMessage struct {
	nodeName string
	buf      []byte
	size     int
}

type PiggybackQueue struct {
	messages Messages
	size     int

	mutex sync.Mutex
}

func (r *Rumor) EnqueuePackedMessage(nodeName string, msgType messageType, msg interface{}) error {
	emsg, err := Encode(msgType, msg)
	if err != nil {
		return err
	}

	bmsg := emsg.Bytes()
	m := &PackedMessage{nodeName: nodeName, buf: bmsg, size: len(bmsg)}
	q, ok := r.piggybackQueMap[nodeName]
	if !ok {
		return errors.New("Unknow queue name")
	}
	q.Enqueue(m)

	return nil
}

func (r *Rumor) GetPiggybackData(nodeName string, limit, overhead int) [][]byte {
	q, ok := r.piggybackQueMap[nodeName]
	if !ok {
		var b [][]byte
		return b
	}

	return q.Get(limit, overhead)
}

func (q *PiggybackQueue) Enqueue(pm *PackedMessage) {
	q.mutex.Lock()
	q.messages = append(q.messages, pm)
	q.size++
	q.mutex.Unlock()
}

func (q *PiggybackQueue) Dequeue() *PackedMessage {
	q.mutex.Lock()
	defer q.mutex.Unlock()

	if q.size <= 0 {
		return nil
	}

	pm := q.messages[0]
	q.messages = q.messages[1:]
	q.size--

	return pm
}

// Get message until limit size
// XXX implment this logic with DP?
func (q *PiggybackQueue) Get(limit, overhead int) [][]byte {
	q.mutex.Lock()
	defer q.mutex.Unlock()

	usedByte := 0
	var sendBytes [][]byte

	if len(q.messages) <= 0 {
		return sendBytes
	}

	for i := 0; i < len(q.messages); i++ {
		pm := q.messages[i]
		if limit < usedByte+pm.size+overhead {
			continue
		}
		usedByte += (pm.size + overhead)
		// XXX check limit message count
		sendBytes = append(sendBytes, pm.buf)

		n := len(q.messages)
		q.messages[i], q.messages[n-1] = q.messages[n-1], nil
		if (n - 1) != i { // not at last
			i-- // Now, i is new value which existed at last of messages array
		}
		q.messages = q.messages[:n-1]
	}

	return sendBytes
}

func (q *PiggybackQueue) Reset() {
	q.mutex.Lock()
	defer q.mutex.Unlock()

	q.messages = nil
	q.size = 0
}

func (q *PiggybackQueue) Size() int {
	q.mutex.Lock()
	defer q.mutex.Unlock()
	return q.size
}
