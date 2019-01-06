require 'thwait'
require 'socket'
require 'logger'
require 'thread'


ADDR = '127.0.0.1'
PORT = 3000
UPSTREAM_PORT = 8000

sock = TCPServer.new(ADDR, PORT)
sock.listen(Socket::SOMAXCONN)

cl = sock.accept
up = TCPSocket.new(ADDR, UPSTREAM_PORT)

t1 = Thread.new do
  v = IO.copy_stream(up, cl)
  puts "<- #{v} bytes"
end

# t2 = Thread.new do
  v = IO.copy_stream(cl, up)
  puts "-> #{v} bytes"
# end

# threads = [t1, t2]
# thall = ThreadsWait.new(*threads)
# p thall.next_wait
# p thall.next_wait
