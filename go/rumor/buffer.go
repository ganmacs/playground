package rumor

import (
	"math"
	"sort"
	"sync"
)

type PackedMessage struct {
	nodeName      string
	buf           []byte
	transmitCount int
	size          int
}

func (m *PackedMessage) Expired(limit float64) bool {
	return float64(m.transmitCount) >= limit
}

type Messages []*PackedMessage

func (m Messages) Len() int {
	return len(m)
}

func (m Messages) Less(i, j int) bool {
	return m[i].transmitCount > m[j].transmitCount
}

func (m Messages) Swap(i, j int) {
	m[i], m[j] = m[j], m[i]
}

type PiggybackBuffer struct {
	NodeSize func() int

	messages    Messages
	size        int
	transmitLam float64

	mutex sync.Mutex
}

func (r *Rumor) PushMessageToBuffer(nodeName string, msgType messageType, msg interface{}) error {
	emsg, err := Encode(msgType, msg)
	if err != nil {
		return err
	}

	bmsg := emsg.Bytes()
	m := &PackedMessage{nodeName: nodeName, buf: bmsg, size: len(bmsg)}
	r.piggybackBuffer.Push(m)
	return nil
}

func (r *Rumor) GetPiggybackData(limit, overhead int) [][]byte {
	return r.piggybackBuffer.Get(limit, overhead)
}

func (q *PiggybackBuffer) Push(pm *PackedMessage) {
	q.mutex.Lock()
	q.messages = append(q.messages, pm)
	q.size++
	q.mutex.Unlock()
}

func (q *PiggybackBuffer) Pop() *PackedMessage {
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
func (q *PiggybackBuffer) Get(limit, overhead int) [][]byte {
	q.mutex.Lock()
	defer q.mutex.Unlock()

	usedByte := 0
	var sendBytes [][]byte

	if len(q.messages) <= 0 {
		return sendBytes
	}

	transmitLimit := q.transmitLimit()

	// messages is ordered by DESC of transimittCount
	for i := len(q.messages) - 1; i >= 0; i-- {
		pm := q.messages[i]
		if limit < usedByte+pm.size+overhead {
			continue
		}
		usedByte += (pm.size + overhead)
		// XXX check limit message count
		sendBytes = append(sendBytes, pm.buf)

		pm.transmitCount++
		if pm.Expired(transmitLimit) {
			n := len(q.messages)
			q.messages[i], q.messages[n-1] = q.messages[n-1], nil
			q.messages = q.messages[:n-1]
		}
	}

	if len(sendBytes) > 0 {
		q.Sort()
	}

	return sendBytes
}

// t * log2(N) where t is parameter and N is number of nodes
func (q *PiggybackBuffer) transmitLimit() float64 {
	nodeNum := q.NodeSize()
	nodeScale := math.Log2(float64(nodeNum))
	return q.transmitLam * nodeScale
}

func (q *PiggybackBuffer) Reset() {
	q.mutex.Lock()
	defer q.mutex.Unlock()

	q.messages = nil
	q.size = 0
}

func (q *PiggybackBuffer) Size() int {
	q.mutex.Lock()
	defer q.mutex.Unlock()
	return q.size
}

// Not thread safe
// XXX check sync.Mutext to be reentrant or not
func (q *PiggybackBuffer) Sort() {
	sort.Sort(q.messages)
}
