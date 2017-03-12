#!/usr/bin/env ruby
$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'leader'
require 'leader/node'

ports = [8080, 8081]

# nodes = ports.map do |port|
#   node = Leader::Node.new(port: port, nodes: ports)
#   Leader.logger.info("starting ... #{node}, port=#{port}")
#   node.start
#   node
# end
event_loop = Cool.io::Loop.default

node = Leader::Node.new(port: 8080)
node.start

c = Leader::Client.new(port: 8080)
c.attach(event_loop)
c.send(:hello)

event_loop.run
# sleep(10000)                    # fix
