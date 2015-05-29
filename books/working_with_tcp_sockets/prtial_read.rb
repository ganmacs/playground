require 'socket'

one_hundred_kb = 1024 * 100

Socket.tcp_server_loop(4481) do |connection|
  begin
    while data = connection.readpartial(one_hundred_kb)
      puts data
    end
  rescue EOFError
    puts 'raise EOFError'
  end

  connection.close
end
