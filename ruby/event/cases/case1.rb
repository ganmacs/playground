#!/usr/bin/env ruby
$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'eve'

ADDR = '127.0.0.1'

sinario = {
  heartbeat_rate: 1,
  nodes: [
    { name: 'leader', addr: ADDR, port: 8000, leader: true, log_output: 'log/leader1' },
    { name: 'node1', addr: ADDR, port: 8001, log_output: 'log/node001' },
    { name: 'node2', addr: ADDR, port: 8002, log_output: 'log/node002' },
    { name: 'node3', addr: ADDR, port: 8003, log_output: 'log/node003' },
    { name: 'node4', addr: ADDR, port: 8004, log_output: 'log/node004' },
  ]
}

Eve.start(sinario)
