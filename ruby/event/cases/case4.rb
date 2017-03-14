#!/usr/bin/env ruby
$LOAD_PATH.unshift File.expand_path('../../lib', __FILE__)
require 'eve'

ADDR = '127.0.0.1'

p = ENV['PORT'].to_i
evloop = Cool.io::Loop.default
option = {
  addr: ADDR,
  evloop: evloop,
  port: p
}

opt = if p == 3000
        option.merge(
          name: 'leader',
          leader: true,
          cluster: [3001, 3002, 3003, 3004].map { |e| "#{ADDR}:#{e}" },
        )
      else
        option.merge(name: "node#{p}")
      end

Eve::Agent.new(opt).start
evloop.run(0.01)
