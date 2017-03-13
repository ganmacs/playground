require_relative 'util'

require "cool.io"
require "logger"

ADDR = "127.0.0.1"
PORT = 4321

$logger = Logger.new(STDOUT)

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

class ClientConnection < Cool.io::TCPSocket
  def initialize(*args)
    super
    @buffer = SafeBuffer.new
    @mutex = Mutex.new
    @connected = false
    @future = Future.new(self) do |result, _|
      close
      result
    end
  end

  def send_request(data)
    @buffer.add(data)
    flash if connected?
    @future
  end

  def on_connect
    $logger.info("[CLIENT] connected #{remote_addr}:#{remote_port}")
    @mutex.synchronize { @connected = true }
    flash
  end

  def on_close
    $logger.info("[CLIENT] closed #{remote_addr}:#{remote_port}")
  end

  def on_read(data)
    @future.set(data)
    $logger.info("[CLIENT] returned from server: #{data}")
  end

  private

  def connected?
    @mutex.synchronize do
      @connected
    end
  end

  def flash
    return unless @buffer.buffered?
    write @buffer.to_data
    $logger.info("[CLIENT] trying sending...")
    @buffer.reset
  end
end

event_loop = Cool.io::Loop.default

# server
server = Cool.io::TCPServer.new(ADDR, PORT, EchoServerConnection)
server.attach(event_loop)
$logger.info "Echo server listening on #{ADDR}:#{PORT}"
server_thread = Thread.new do
  event_loop.run
end

Ticker.start(5) do
  begin
    client = ClientConnection.connect(ADDR, PORT)
    client.attach(event_loop)
    future = client.send_request("hello!!")
    $logger.info("[CLIENT] #{future.get}") # blocking
  end
end

server_thread.join
