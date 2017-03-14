require "cool.io"
require "eve/safe_buffer"
require "eve/future"

module Eve
  class Client
    def initialize(addr, port, evloop, logger)
      @addr = addr
      @port = port
      @evloop = evloop
      @logger = logger
    end

    def request(data)
      client = ClientConnection.connect(@addr, @port, @logger)
      @evloop.attach(client)
      future = client.send_request(data)
      @logger.info("[CLIENT] #{future.get}") # blocking
    end

    class ClientConnection < Cool.io::TCPSocket
      def initialize(io, logger)
        super(io)
        @logger = logger
        @buffer = SafeBuffer.new
        @mutex = Mutex.new
        @connected = false
        @future = Future.new(self) do |result, err|
          if err == "connection failed"
            err
          elsif err
            close
            err
          else
            close
            result
          end
        end
      end

      def send_request(data)
        @buffer.add(data)
        flash if connected?
        @future
      end

      def on_connect
        @logger.debug("[CLIENT] connected #{remote_addr}:#{remote_port}")
        @mutex.synchronize { @connected = true }
        flash
      end

      def on_close
        @logger.debug("[CLIENT] closed #{remote_addr}:#{remote_port}")
      end

      def on_read(data)
        @future.set(data)
        @logger.debug("[CLIENT] returned from server: #{data}")
      end

      def on_connect_failed
        @logger.error("connect failed, meaning our connection to their port was rejected")
        @future.cancel("connection failed")
        close if connected?
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
        @logger.debug("[CLIENT] trying sending...")
        @buffer.reset
      end
    end
  end
end
