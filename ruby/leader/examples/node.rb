#!/usr/bin/env ruby
$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'leader'
require 'leader/node'

PORTS = [8080, 8081, 8082, 8083]

node = Leader::Node.new(nodes: PORTS)
node.start
