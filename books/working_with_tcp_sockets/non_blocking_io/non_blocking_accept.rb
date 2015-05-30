require 'socket'

server = TCPServer.new(4481)

loop do
  begin
    connection = servers.accept_nonblock
  rescue Errno::EAGAIN
    retry
  end

  connection.close
end
