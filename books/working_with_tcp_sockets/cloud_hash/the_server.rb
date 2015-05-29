require 'socket'

module CloudHash
  class Server
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
      request = connection.read
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
