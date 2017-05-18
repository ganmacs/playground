package rumor

import (
	"log"
	"os"
)

type Rumor struct {
	Name string

	// states   []*state // FIXME?
	stateMap map[string]*state

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
	ru := &Rumor{
		Name:   config.Name,
		logger: log.New(os.Stdout, "[Rumor] ", log.LstdFlags),
	}

	return ru, nil
}

func (ru *Rumor) becomeAlive() error {
	v, ok := ru.stateMap[ru.Name]
	if !ok {
		a := newState()
	}

	// return rumor.state.becomeAlive()
}
