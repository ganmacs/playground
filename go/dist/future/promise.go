package future

type Promise interface {
	Get() (Value, error)

	Then(func(Value) (Value, error)) Promise
}

type PromiseResult FutureResult

func NewPromise(f func() (Value, error)) Promise {
	promise := PromiseResult{result: make(chan *result)}

	go func() {
		value, error := f()
		promise.result <- &result{value, error}
	}()

	return promise
}

func (p PromiseResult) Get() (Value, error) {
	res := <-p.result
	return res.value, res.error
}

func (p PromiseResult) Then(fn func(Value) (Value, error)) Promise {
	promise := &PromiseResult{result: make(chan *result)}

	go func() {
		res := <-p.result

		if res.error != nil {
			promise.result <- res
			return
		}

		value, error := fn(res.value)
		promise.result <- &result{value, error}
	}()

	return promise
}
