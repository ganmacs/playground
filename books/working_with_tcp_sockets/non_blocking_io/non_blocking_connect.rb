require 'socket'

socket = Socket.new(:INET, :STREAM)
remote_addr = Socket.pack_sockaddr_in(80, 'google.com')

begin
  socket.connect_nonblock(remote_addr)
rescue Errno::EINPROGRESS
# operation is in progress
rescue Errno::EALREADY
# A previous nonblocking connect is already i n progress
rescue Errno::ECONNREFUSED
  # The remote host refused our connect
end
