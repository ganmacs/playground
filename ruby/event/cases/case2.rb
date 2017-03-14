#!/usr/bin/env ruby
$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'eve'

ADDR = '127.0.0.1'

nodes = 100.times.map do |i|
  v = "%03d" % i
  { name: "node#{i}", addr: ADDR, port: 3001 + i, log_output: "log/node#{v}" }
end

sinario = {
  heartbeat_rate: 1,
  nodes: [
    { name: 'leader', addr: ADDR, port: 3000, leader: true, log_output: 'log/leader1' },
  ] + nodes
}

Eve.start(sinario)
