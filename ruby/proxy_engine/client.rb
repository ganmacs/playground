require 'socket'
require 'httpclient'
ADDR = '127.0.0.1'
PORT = 3000

# client = HTTPClient.new
# client.debug_dev=STDOUT #デバックデータの出力先として「STDOUT」を設定
# client.get_content("http://#{ADDR}:#{PORT}")

v = StringIO.new
f2 = open('client.rb')

r, w = IO.pipe

thread = Thread.new do
  1000.times do
    p IO.copy_stream(r, v, 1)
    p v.string
  end
end

sleep(1)

IO.copy_stream(f2, w)

# k = StringIO.new
# k << "a"

thread.join

p v.string
