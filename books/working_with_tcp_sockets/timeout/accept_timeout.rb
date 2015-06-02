require 'socket'

server = TCPServer.new(4481)
timeout = 5

begin
  server.accept_nonblock
rescue Errno::EAGAIN
  # accept前
  if IO.select([server], nil, nil, timeout)
    retry
  else
    raise Timeout::Error
  end
end
