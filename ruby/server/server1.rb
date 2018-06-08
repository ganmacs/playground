require "socket"

gs = TCPServer.open('127.0.0.1', '3000')
addr = gs.addr
addr.shift
printf("server is on %s\n", addr.join(":"))

while true
  Thread.start(gs.accept) do |s|
    print(s, " is accepted\n")
    while s.gets
      s.write($_)
    end

    print(s, " is gone\n")
    s.close
  end
end
