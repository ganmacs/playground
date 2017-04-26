package istm

type operation struct {
	kind       int
	readValue  int
	writeValue int
}

const (
	readOperation = iota
	writeOperation
	readWriteOperation
)

func newReadTVarLog(v int) *operation {
	return &operation{
		kind:      readOperation,
		readValue: v,
	}
}

func newWriteTVarLog(v int) *operation {
	return &operation{
		kind:       writeOperation,
		writeValue: v,
	}
}

func (t *operation) read() int {
	return t.readValue
}

func (t *operation) write(v int) {
	if t.kind == readOperation {
		t.kind = readWriteOperation
	}

	t.writeValue = v
}
