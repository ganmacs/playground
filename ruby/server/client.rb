require 'socket'

PEER_PORT = 3001
PEER_ADDR = '127.0.0.1'

s = TCPSocket.open(PEER_ADDR, PEER_PORT)

s.write("asdfghj\n")
p s.gets
# sleep 10
