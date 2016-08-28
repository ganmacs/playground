require "socket"

# input.start -> (Matched output.emit) -> (buffer.emit -> Writer.write)

# s = TCPSocket.open("localhost", 8080)

require 'stringio'

io = StringIO.new("hello") do |x|
  p x
end

p io.string
io.puts "Hello World"
p io.string #=> "Hello World\n"
io.close
