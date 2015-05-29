require 'socket'

# # create
# server = Socket.new(:INET, :STREAM)

# # bind
# addr = Socket.pack_sockaddr_in(4481, '0.0.0.0')
# server.bind(addr)

# # listen
# server.listen(128)

# loop do
#   # accept
#   connection, _ = server.accept

#   # handle connection

#   # close
#   connection.close
# end

# servers = Socket.tcp_server_sockets(4481)
# Socket.accept_loop(servers) do |connection|
#   connection.close
# end

socket = Socket.new(:INET, :STREAM)
remote_addr = Socket.pack_sockaddr_in(80, 'google.com')
socket.connect(remote_addr)
