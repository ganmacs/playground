require 'socket'
require 'timeout'

socket = Socket.new(:INET, :STREAM)
remote_addr = Socket.pack_sockaddr_in(80, 'google.com')
timeout = 5                     # secondsd

begin
  socket.connect_nonblock(remote_addr)
rescue Errno::EINPROGRESS
  if IO.select(nil, [socket], nil, timeout)
    retry
  else
    raise Timeout::Error
  end
rescue Errno::EISCONN
  socket.write('ohai')
  socket.close
end
