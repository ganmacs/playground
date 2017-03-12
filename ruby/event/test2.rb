require "cool.io"
require "logger"

ADDR = "127.0.0.1"
PORT = 4321

$logger = Logger.new(STDOUT)

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
    @connect = false
  end

  def send_request(data)
    @buffer.add(data)
    # reach following code before estaching connection
    flash if connected?
  end

  def detach
    case
    when connected? && @buffer.buffered?
      flash
      super
      $logger.info("[CLIENT] detach #{remote_addr}:#{remote_port}")
    when !connected? && @buffer.buffered?
      Thread.new do
        sleep(0.1) until connected?        # how it goes when connection alread done
        flash
        super
        $logger.info("[CLIENT] detach #{remote_addr}:#{remote_port}")
      end
    else
      super
      $logger.info("[CLIENT] detach #{remote_addr}:#{remote_port}")
    end
  end

  def on_connect
    $logger.info("[CLIENT] connected #{remote_addr}:#{remote_port}")
    @mutex.synchronize do
      @connect = true
    end
    flash
  end

  def on_close
    $logger.info("[CLIENT] closed #{remote_addr}:#{remote_port}")
  end

  def on_read(data)
    $logger.info("[CLIENT] returned from server: #{data}")
    close
  end

  private

  def connected?
    @mutex.synchronize do
      @connect
    end
  end

  def flash
    return unless @buffer.buffered?
    write @buffer.to_data
    $logger.info("[CLIENT] trying sending...")
    @buffer.reset
  end

  class SafeBuffer
    def initialize
      @mutex = Mutex.new
      @buffer = ""
    end

    def to_data
      @mutex.synchronize do
        @buffer
      end
    end

    def flash
      return false unless buffered?
      write @buffer
      reset_buffer
      true
    end

    def add(data)
      v = data.to_s           # is #to_s ok?
      @mutex.synchronize do
        @buffer << v
      end
    end

    def reset
      @mutex.synchronize do
        @buffer = ""
      end
    end

    def buffered?
      @mutex.synchronize do
        !@buffer.empty?
      end
    end
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
    client.send_request("hello!!")
    $logger.info "Echo client connecting to #{ADDR}:#{PORT}"
  ensure
    client.detach
  end
end

server_thread.join
