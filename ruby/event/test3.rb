require_relative 'agent'
require "logger"

ADDR = "127.0.0.1"
PORT = 4321

$logger = Logger.new(STDOUT)

event_loop = Cool.io::Loop.default

# leader
Agent.new(ADDR, PORT, event_loop, client_ports: [4230]).start

Agent.new(ADDR, 4230, event_loop).start


event_loop.run
