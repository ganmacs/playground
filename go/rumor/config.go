package rumor

import (
	"os"
	"time"
)

type Config struct {
	Name string

	BindAddr string
	BindPort int

	GossipPeriod time.Duration
	GossipCount  int

	ProbeInterval time.Duration
	ProbeTimeout  time.Duration

	RumorIterval   time.Duration
	RumorNodeCount int
	transport      *Transport
}

func DefaultConfig() *Config {
	hostname, _ := os.Hostname()
	return &Config{
		Name:           hostname,
		BindAddr:       "0.0.0.0",
		BindPort:       8000,
		GossipPeriod:   3,
		GossipCount:    1,
		ProbeInterval:  2,
		ProbeTimeout:   1,
		RumorIterval:   time.Second * 2,
		RumorNodeCount: 3,
	}
}
