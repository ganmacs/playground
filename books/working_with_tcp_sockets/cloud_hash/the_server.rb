require 'socket'

module CloudHash
  class Server
    SIZE_OF_INT = [11].pack('i').size

    def initialize(port)
      @server = TCPServer.new(port)
      puts "Listening on port #{@server.local_address.ip_port}"
      @strage = {}
    end

    def start
      Socket.accept_loop(@server) do |connection|
        handle(connection)
        connection.close
      end
    end

    def handle(connection)
      packed_msg_length = connection.read(SIZE_OF_INT)
      msg_length = packed_msg_length.unpack('i').first
      request = connection.read(msg_length)
      connection.write process(request)
    end

    def process(request)
      command, key, value = request.split
      case command.upcase
      when 'GET'
        @strage[key]
      when 'SET'
        @strage[key] = value
      end
    end
  end
end

server = CloudHash::Server.new(4481)
server.start
