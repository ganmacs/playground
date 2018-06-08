require 'socket'

PORT = 3001
ADDR = '127.0.0.1'

PEER_PORT = 3000
PEER_ADDR = '127.0.0.1'

sock = TCPServer.new(ADDR, PORT)
sock.listen(Socket::SOMAXCONN)  # TODO make backlog configurable if necessary

while (v = sock.accept)
  Thread.new do
    upstream = TCPSocket.open(PEER_ADDR, PEER_PORT)
    t1 = Thread.new do
      IO.copy_stream(v, upstream)
    end

    t2 = Thread.new do
      IO.copy_stream(upstream, v)
    end

    t1.join

    puts " #{v} close"
    upstream.close                     # ok?

    t2.join
  end
end
