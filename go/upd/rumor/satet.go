package rumor

type stateType int

const (
	aliveState stateType = iota
	deadState
)

type state struct {
	stateType stateType
}

func newState() *state {
	return &state{
		stateType: aliveState,
	}
}

func (s *state) becomeAlive() error {

}
