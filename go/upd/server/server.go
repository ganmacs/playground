package main

import (
	"log"
)

type Server struct {
	name      string
	ch        chan *Packet
	logger    *log.Logger
	transport Transport
}

func NewServer() *Server {
	server := &Server{
		name:   "name",
		ch:     make(chan *Packet),
		logger: new(log.Logger),
	}

	return server
}
