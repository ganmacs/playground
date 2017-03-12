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
  def send_request
    $logger.info("[CLIENT] sending data...")
  end

  def on_connect
    $logger.info("[CLIENT] connected #{remote_addr}:#{remote_port}")
  end

  def on_close
    $logger.info("[CLIENT] closed #{remote_addr}:#{remote_port}")
  end

  def on_read(data)
    $logger.info("[CLIENT] returned from server: #{data}")
    close
  end
end

class Ticker
  def self.start(duraiton, &block)
    new.start(duraiton, block)
  end

  def start(duraiton, block)
    t = Thread.current
    @t = Thread.new do
      loop do
        begin
          block.call
          sleep duraiton
        rescue => e
          t.raise(e)            # ok?
          break
        end
      end
    end
  end

  def stop
    @t.kill
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

Ticker.start(2) do
  begin
    client = ClientConnection.connect(ADDR, PORT)
    client.attach(event_loop)
    client.send_request
    $logger.info "Echo client connecting to #{ADDR}:#{PORT}"
  ensure
    Thread.new do
      sleep 2                   # wait to send data
      client.detach
      $logger.info "detached!!!"
    end
  end
end

server_thread.join
