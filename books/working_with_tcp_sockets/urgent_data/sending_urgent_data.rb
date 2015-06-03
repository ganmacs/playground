require 'socket'

socket = TCPSocket.new('localhost', 4481)

socket.write 'first'
socket.write 'second'

socket.send('!', Socket::MSG_OOB)
