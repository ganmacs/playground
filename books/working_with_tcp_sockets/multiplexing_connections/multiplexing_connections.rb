require 'socket'

tcp_socket0 = TCPSocket.new('localhost', 4481)
tcp_socket1 = TCPSocket.new('localhost', 4481)
tcp_socket2 = TCPSocket.new('localhost', 4481)

connections = [tcp_socket0, tcp_socket1, tcp_socket2]

loop do
  ready = IO.select(connections)
  readable_connections = ready[0]
  readable_connections.each do |conn|
    data = conn.readpartial(4096)
    puts data
    # process(data)
  end
end


# loop do
#   connections.each do |conn|
#     begin
#       data = conn.read_nonblock(4096)
#       puts data
#       # process(data)
#     rescue Errno::EAGAIN
#     end
#   end
# end
