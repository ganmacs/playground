require 'socket'

client = TCPSocket.new('localhost', 4481)
client.write('gekko')
client.close
