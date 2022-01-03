require 'socket'

s = TCPSocket.open("127.0.0.1", "6379")
s.write("*1\r\n$4\r\nPING\r\n")
puts s.gets
