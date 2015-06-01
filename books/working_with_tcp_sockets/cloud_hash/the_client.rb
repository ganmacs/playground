require 'socket'

module CloudHash
  class Client
    attr_accessor :host, :port

    def initialize(host, port)
      @connection = TCPSocket.new(host, port)
    end

    def get(key)
      request "GET #{key}"
    end

    def set(key, value)
      request "SET #{key} #{value}"
    end

    def request(string)
      @connection.puts(string)
      @connection.gets
    end
  end
end

# cloud_hash = CloudHash::Client.new('localhost', 4481)
# puts cloud_hash.set 'prez', 'obama'
# puts cloud_hash.get 'prez'
# puts cloud_hash.get 'vp'

payload = 'SET prez obama'
msg_length = payload.size
packed_msg_length = [msg_length].pack('i')

connection = TCPSocket.new('localhost', 4481)
connection.write(packed_msg_length)
connection.write(payload)
