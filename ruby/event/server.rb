require_relative "client"
require "cool.io"

class Server
  def initialize(addr, port, loop)
    @addr = addr
    @port = port
    @loop = loop
  end

  def listen
    $logger.info "Echo server listening on #{@addr}:#{@port}"
    @server = Cool.io::TCPServer.new(@addr, @port, EchoServerConnection)
    @loop.attach(@server)
  end

  class EchoServerConnection < Cool.io::TCPSocket
    def on_connect
      $logger.info("[SERVER] connected #{remote_addr}:#{remote_port}")
    end

    def on_close
      $logger.info("[SERVER] closed #{remote_addr}:#{remote_port}")
    end

    def on_read(data)
      write data
    end
  end
end
