require 'socket'

Socket.tcp_server_loop(4481) do |connection|
  puts connection.read

  connection.close
end
