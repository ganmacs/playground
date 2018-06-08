require 'socket'

class LoadBlancer
  def initialize(addr, port, backends, logger)
    @logger = logger
    @addr = addr
    @port = port
    @backends = backends
    @sock = listen_tcp
  end

  def run
    while (sock = @sock.accept)
      Thread.new do
        begin
          bc = @backends.choose
          @logger.info("Connect to #{bc[:addr]}:#{bc[:port]}")
          upstream = TCPSocket.open(bc[:addr], bc[:port])

          @logger.info("Connect to #{bc[:addr]}:#{bc[:port]}")

          t1 = Thread.new do
            IO.copy_stream(sock, upstream)
          end

          Thread.new do
            # would be raise an error: Bad file descriptor - read (Errno::EBADF)
            IO.copy_stream(upstream, sock)
          end

          t1.join

          @logger.info("Close connect for #{bc[:addr]}:#{bc[:port]}")
          upstream.close                     # XXX

          @logger.info("Finish connect for #{bc[:addr]}:#{bc[:port]}")
        rescue => e
          @logger.error(e)
        end
      end
    end
  end

  def stop
    @sock.close
  end

  private

  def listen_tcp
    @logger.info("Start listen #{@addr}:#{@port}")
    sock = TCPServer.new(@addr, @port)
    sock.listen(Socket::SOMAXCONN)
    sock
  end
end

class RoundRobin
  def initialize(backends)
    @backends = backends
    @mutex = Mutex.new
    @size = backends.size
    @i = 0
  end

  def choose
    bc = @backends[@i]

    # XXX
    @mutex.synchronize do
      @i += 1

      if @i >= @size
        @i = 0
      end
    end
    bc
  end
end
