
    # require 'cool.io'
# HOST = 'localhost'
# PORT = 4321

# class EchoServerConnection < Cool.io::TCPSocket
#   def on_connect
#     puts "#{remote_addr}:#{remote_port} connected"
#   end

#   def on_close
#     puts "#{remote_addr}:#{remote_port} disconnected"
#   end

#   def on_read(data)
#     write data
#   end
# end

# server = Cool.io::TCPServer.new(HOST, PORT, EchoServerConnection)
# server.attach(Cool.io::Loop.default)

# puts "Echo server listening on #{HOST}:#{PORT}"
# Cool.io::Loop.default.run
