require 'socket'

Socket.tcp_server_loop(4481) do |connection|
  connection.write('welcome')
  connection.clsoe
end
