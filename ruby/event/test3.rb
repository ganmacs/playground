require_relative 'util'
require_relative 'server'
require_relative 'client'
require "logger"

ADDR = "127.0.0.1"
PORT = 4321

$logger = Logger.new(STDOUT)

event_loop = Cool.io::Loop.default

Server.new(ADDR, PORT, event_loop).listen
i = 0

Ticker.start(5) do
  client = Client.new(ADDR, PORT, event_loop)
  client.request("hello!! #{i}")
  i += 1
end

event_loop.run
