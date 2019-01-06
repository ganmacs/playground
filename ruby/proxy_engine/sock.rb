require 'thwait'
require 'socket'
require 'sinatra/base'
require 'logger'
require 'thread'
require 'stackprof'
require 'timeout'

$logger = Logger.new(STDOUT)

ADDR = '127.0.0.1'
PORT = 3000
UPSTREAM_PORT = 8000

@stop = false

# class ConnectionPool
#   MAX_CONN = 1
#   Conn = Struct.new(:id, :conn)

#   # @parms [Array] backends [{ addr: ..., port: ... }, { addr: .., ...}, ...]
#   def initialize(backends:, timeout: 60, max_connection: MAX_CONN)
#     @max_connection = max_connection
#     @timeout = timeout
#     @mutex = Mutex.new

#     @i = 0
#     @backends = backends
#     @backend_size = backends.size
#     @pool = []
#     @pool_size = []
#     @pool_size_mutext = Mutex.new

#     backends.size.times do
#       @pool_size << 0
#       @pool << Queue.new
#     end
#   end

#   # MUST be call with #return_connection
#   def get_connnection
#     i = next_backend_idx
#     conns = @pool[i]
#     conns.pop(true)
#   rescue ThreadError => _
#     # queue is empty
#     @pool_size_mutext.synchronize do
#       if @pool_size[i] < @max_connection
#         @pool_size[i] += 1
#         b = @backends[i]
#         return Conn.new(i, create_connnection(b[:addr], b[:port]))
#       end
#     end

#     # XXX
#     puts "wait!!!"
#     conns.pop
#   end

#   def return_connection(conn)
#     @pool[conn.id].enq conn
#   end

#   private

#   def create_connnection(addr, port)
#     TCPSocket.open(addr, port)
#   end

#   def next_backend_idx
#     @mutex.synchronize do
#       i = @i
#       @i += 1
#       @i = 0 if @i >= @backend_size
#       i
#     end
#   end
# end

def sock_open_with_timeout(port, addr, timeout: 10)
  socket = Socket.new(Socket::AF_INET, Socket::SOCK_STREAM, 0) # tcp socket
  sockaddr = Socket.sockaddr_in(addr, port)

  begin
    socket.connect_nonblock(sockaddr)
  rescue IO::WaitWritable
    if IO.select(nil, [socket], nil, timeout)
      begin
        socket.connect_nonblock(sockaddr)
      rescue Errno::EISCONN
      # connected
      rescue => e
        socket.close
        raise e
      end
    else
      socket.close
      raise "Connection timeout"
    end
  end

  socket
end

def run(sock)
  que = Queue.new
  que2 = Queue.new
  # connection_pool = ConnectionPool.new(backends: [{ addr: '127.0.0.1', port: 8000 }])

  t = Thread.new do
    begin
      loop do
        que2.enq 1
        que.enq sock.accept
      end
    rescue => e
      puts "in sock.accpet #{e}"
    end
  end

  Thread.new do
    until @stop
      sleep(1)
    end

    que.clear

    100.times do
      que.enq false
    end
  end

  Thread.new do
    loop do
      sleep(1)
      if @stop
        break
      end

      c = 0
      ObjectSpace.each_object(IO) do |f|
        if f.closed?
        # $logger.info("#{f} is closed")
        else
          c += 1
        end
      end

      $logger.info "sock #{sock}, stacked_request #{que.size}, processing: #{que2.size-1}, free worker #{que.num_waiting},open fd: #{c}"
    end
  end

  16.times.map {
    Thread.new(que) do |q|
      while (s = q.pop)
        begin
          # conn = pool.get_connnection
          # upstream = conn.conn
          upstream = sock_open_with_timeout('127.0.0.1', 8000)
          $logger.info("upstream: #{upstream}, upstream.closed?: #{upstream.closed?}")

          t1 = Thread.new do
            begin
              size = IO.copy_stream(s, upstream)
              $logger.info("t1: copy #{size}bytes")
            rescue => e
              $logger.info("t1: s.closed? #{s.closed?}, upstream.closed? #{upstream.closed?}, #{e}")
            ensure
              $logger.info("t1 ensure: s.closed? #{s.closed?}, upstream.closed? #{upstream.closed?}")
            end
          end

          t2 = Thread.new do
            begin
              Thread.pass
              size = IO.copy_stream(upstream, s)
              $logger.info("t2: copy #{size}bytes")
            rescue => e
              $logger.info("t2: s.closed? #{s.closed?}, upstream.closed? #{upstream.closed?}, #{s.eof?},#{upstream.eof?},#{e}")
            ensure
              $logger.info("t2 ensure: s.closed? #{s.closed?}, upstream.closed? #{upstream.closed?}")
            end
          end

          threads = [t1, t2]
          thall = ThreadsWait.new(*threads)
          finish = thall.next_wait        # wait for first one thread

          if t2 == finish
            $logger.info("t2 finish first: wait t1 s.closed? #{s.closed?}, upstream.closed? #{upstream.closed?}")
            t1.join
          else
            $logger.info('t1 finish first')
          end
        rescue => e
          puts "in worker #{e}"
        ensure
          pool.return_connection(conn)
          que2.pop
          s.close
          Thread.new do
            sleep 15
            p "t2 killed"
            Thread.kill(t2)
          end
        end
      end
    end
  }
  t.join
end

# my_app = Sinatra.new {
#   set :port, UPSTREAM_PORT
#   get('/') { "hi" }
# }

# s = SimpleServer.new(ADDR, UPSTREAM_PORT, $logger, 1)

sock = TCPServer.new(ADDR, PORT)
sock.listen(Socket::SOMAXCONN)

p Socket::SOMAXCONN

Signal.trap(:INT) {
  sock.close
  @stop = true
}

# Thread.new do
#   my_app.run!
# end

p Process.pid
StackProf.run(mode: :cpu, out: 'tmp/stackprof.dump', interval: 1000) do
  run(sock)
  # sleep(60)
end
