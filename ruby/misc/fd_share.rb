require 'socket'

module SocketProxy
  PATH = "SocketProxy_#{Process.pid}_".freeze

  class Server
    def initialize(size, strategy)
      @size = size
      @strategy = strategy
      @servers = {}
      @wait_queue = Queue.new

      start
    end

    def start
      @size.each do |i|
        k = PATH + i.to_s
        begin
          old_umask = File.umask(0077)
          @servers[k] = UNIXServer.new(k)
        ensure
          File.umask(old_umask)
        end
      end

      @thread = Thread.new do
        loop do
          while (speer = @servers[i].accept)
            Thread.new(speer) do |peer|
              loop do
                if peer.read(1)
                end
              end
            end
          end

          rs, _ = IO.select([ss], [])
          rs.each do |s|
            conn =
              begin
                s.accept_nonblock
              rescue IO::WaitReadable, Errno::EINTR => _
                # nothing
              end
            next unless conn
          end

          sock = pick_server
          if sock.read_nonblock(1, exception: false) == :wait_readable
            next
          end

          q = @wait_queue.pop
          sock.send_io(q)
          q.close
        end
      end
    end

    def stop
      @thread
    end

    def pick_server
      # strategy
      rs, _ = IO.select([ss], [])
    end
  end
end


class Server
  def call
    File.unlink('socket1')
    File.unlink('socket2')
    server1 = UNIXServer.new('socket1')

    server2 = UNIXServer.new('socket2')
    v = Queue.new
    socks = {
      server1 => 0,
      server2 => 0,
    }

    # socks = {}
    # socks << {}
    # [0, server1.accept]
    # socks << [0, server2.accept]

    Thread.new(socks) do |socks|
      begin
        asocks = socks.keys
        loop do
          ios, _ = IO.select([asocks], [])
          ios.each do |io|
            _ = io[0].read(1)
            vv = v.pop
            io.send_io(vv)
            vv.close

            socks[io] += 1
          end
        end
      rescue => e
        p e
      end
    end

    sock = TCPServer.new(50051)
    sock.listen(Socket::SOMAXCONN)  # TODO make backlog configurable if necessary
    while s = sock.accept
      v.push(s)
    end
  end
end

fork do
  sleep 1
  sock = UNIXSocket.new('socket1')

  loop do
    sock.write_nonblock('v')
    fd = sock.recv_io(TCPSocket)
    puts "socket1"
    sleep 1

    puts fd.gets
    fd.puts("hi")
    fd.close
  end
end

fork do
  sleep 1
  sock = UNIXSocket.new('socket2')

  loop do
    sock.write_nonblock('v')
    fd = sock.recv_io(TCPSocket)
    puts "socket2"
    puts fd.gets
    fd.puts("hi")
    fd.close
  end
end

Server.new.call
