require 'socket'

one_kb = 1024                   # bytes

Socket.tcp_server_loop(4481) do |connection|
  while data = connection.read(one_kb)
    puts data
  end

  connection.close
end
