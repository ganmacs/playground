require 'socket'
require 'timeout'

timeout = 5                     # second

Socket.tcp_server_loop(4481) do |connection|
  begin
    connection.read_nonblock(4096)
  rescue Errno::EAGAIN
    # コネクションがあってからtimeout秒か
    if IO.select([connection], nil, nil, timeout)
      retry
    else
      raise Timeout::Error
    end
  end

  connection.close
end
