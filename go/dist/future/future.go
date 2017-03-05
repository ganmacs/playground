package future

const (
	Fulfilled = iota
	Pending   = iota
	Reject    = iota

	fulfilledStr = "fullfilled"
	pendingStr   = "pending"
	rejectStr    = "reject"
)

type Value interface{}

type result struct {
	value Value
	error error
}

type FutureResult struct {
	result chan *result
	state  int
	value  Value
}

type Future interface {
	Get() (Value, error)
	State() string
}

func NewFuture(fn func() (Value, error)) Future {
	fr := &FutureResult{
		result: make(chan *result),
		state:  Pending,
		value:  nil,
	}

	go func() {
		value, error := fn()

		if error == nil {
			fr.state = Fulfilled
		} else {
			fr.state = Reject
		}

		fr.result <- &result{value, error}
	}()

	return fr
}

func (f FutureResult) State() string {
	switch f.state {
	case Fulfilled:
		return fulfilledStr
	case Reject:
		return rejectStr
	case Pending:
		return pendingStr
	default:
		return "unreachable"
	}
}

func (f FutureResult) Get() (Value, error) {
	if f.value != nil {
		return f.value, nil
	}

	v := <-f.result
	return v.value, v.error
}
