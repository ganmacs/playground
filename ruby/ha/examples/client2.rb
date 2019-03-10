require "socket"
v = ::TCPSocket.new('127.0.0.1', '3000')
v.write("abcd\n")
v.close
