require "cool.io"

module Eve
  class Server
    def initialize(addr, port, loop, logger, name = nil)
      @addr = addr
      @port = port
      @loop = loop
      @logger = logger
      @name = name
    end

    def listen
      @logger.info "Echo server listening on #{@addr}:#{@port}"
      @server = Cool.io::TCPServer.new(@addr, @port, EchoServerConnection, @logger, @name)
      @loop.attach(@server)
    end

    class EchoServerConnection < Cool.io::TCPSocket
      def initialize(io, logger, name)
        super(io)
        @name = name
        @logger = logger
      end

      def on_connect
        @logger.debug("[SERVER] connected #{remote_addr}:#{remote_port}")
      end

      def on_close
        @logger.debug("[SERVER] closed #{remote_addr}:#{remote_port}")
      end

      def on_read(data)
        @logger.info("[SERVER] recv data #{remote_addr}:#{remote_port}")
        write("#{data}:#{@name}")
      end
    end
  end
end
