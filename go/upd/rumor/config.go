package rumor

import (
	"os"
	"time"
)

type Config struct {
	Name string

	BindAddr string
	BindPort int

	RumorIterval   time.Duration
	RumorNodeCount int
}

func DefaultConfig() *Config {
	hostname, _ := os.Hostname()
	return &Config{
		Name:           hostname,
		BindAddr:       "0.0.0.0",
		BindPort:       8000,
		RumorIterval:   time.Second * 2,
		RumorNodeCount: 3,
	}
}
