require 'socket'

socket = Socket.new(:INET, :STREAM)
remote_addr = Socket.pack_sockaddr_in(80, 'google.com')

begin
  socket.connect_nonblock(remote_addr)
rescue Errno::EINPROGRESSS
  IO.select(nil, [socket])

  begin
    socket.connect_nonblock(remote_addr)
  rescue Errno::EISCONN
  # success
  rescue Errno::ECONNREFUSED
    # refused by remote host
  end
end
