require_relative 'util'
require 'cool.io'

class Client
  def initialize(addr, port, evloop)
    @addr = addr
    @port = port
    @evloop = evloop
  end

  def request(data)
    client = ClientConnection.connect(@addr, @port)
    @evloop.attach(client)
    future = client.send_request(data)
    $logger.info("[CLIENT] GET #{future.get}") # blocking
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


end
