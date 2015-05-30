require 'socket'

client = TCPSocket.new('localhost', 4481)
payload = 'Lorem ipsum' * 50_000 # 10_000 is too small to flash buffer?


begin
  loop do
    bytes = client.write_nonblock(payload)
    break if bytes >= payload.size
    payload.slice!(0, bytes)
    IO.select(nil, [client])
  end
rescue Errono::EAGAIN
  IO.select(nil, [client])
  retry
end
