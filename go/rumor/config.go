package rumor

import (
	"time"

	"github.com/ganmacs/playground/go/rumor/logger"
)

type Config struct {
	BindAddr string
	BindPort int

	GossipPeriod time.Duration
	GossipCount  int

	ProbeInterval time.Duration
	ProbeTimeout  time.Duration

	RumorIterval   time.Duration
	RumorNodeCount int
	transport      *Transport

	TransmitLammda float64

	Logger *logger.Logger
}

func DefaultConfig() *Config {
	return &Config{
		BindAddr:       "0.0.0.0",
		BindPort:       8000,
		GossipPeriod:   3,
		GossipCount:    1,
		ProbeInterval:  2,
		ProbeTimeout:   time.Second * 2,
		RumorIterval:   time.Second * 2,
		RumorNodeCount: 3,
		TransmitLammda: 2,
	}
}
