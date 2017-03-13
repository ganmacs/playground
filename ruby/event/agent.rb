require_relative 'server'
require_relative 'client'
require_relative 'util'

class Agent
  def initialize(addr, port, evloop, client_ports: [])
    @addr = addr
    @port = port
    @loop = evloop
    @client_ports = client_ports
    @server = Server.new(@addr, @port, @loop)
    @clients = @client_ports.map do |po|
      Client.new(@addr, po, @loop) # adder should be fixed
    end
  end

  def start
    @server.listen
    Ticker.start(2) do
      heartbeat
    end
  end

  private

  def heartbeat
    @clients.each do |c|
      $logger.info("-- heartbeating")
      c.request("hello!! Here is #{c}")
    end
  end
end
