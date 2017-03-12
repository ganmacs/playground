require 'json'

require 'leader/connection'
require 'leader/handler'
require 'leader/ticker'

module Leader
  class Node
    DEFAULT_HOST = '127.0.0.1'
    DEFAULT_PORT = 4321
    # DEFAULT_LOOP = Cool.io::Loop.default

    def initialize(host: ENV['LEADER_HOST'], port: ENV['LEADER_PORT'], nodes: [])
      @handler = Leader::Handler.new
      @host = host || DEFAULT_HOST
      @port = port || DEFAULT_PORT
      @loop = Cool.io::Loop.new
      @nodes = nodes - [@port]
    end

    def start
      Leader.logger.info("starting ... #{@host}:#{@port}")
      attach                    # TODO manage attached node
      t = Thread.new do
        @loop.run
      end
      start_heartbeat
      t.join                    # block
    end

    def on_request(conn, method_name, params)
      handle_request(conn, method_name, params)
    end

    private

    def start_heartbeat
      t = Leader::Ticker.new(5) { broadcast }
      t.start
    end

    def broadcast
      threads = clients.map do |e|
        Thread.new(e) do |cli|
          cli.send(:hello)
        end
      end

      threads.each(&:join)
    end

    def attach
      begin
        @loop.attach(server)
        clients.each do |c|
          c.attach(@loop)
        end
      rescue => e
        Leader.logger.error("raised error at attach #{e}")
        exit 1                  # FIX
      end
    end

    def server
      @server ||= Cool.io::TCPServer.new(@host, @port, Leader::ServerConnection, self)
    end

    def clients
      @clients ||= @nodes.map do |port|
        Leader::Client.new(host: 'localhost', port: port)
      end
    end

    def handle_request(conn, method_name, params)
      r = @handler.send(method_name, params)
      conn.send_response(result: r, error: [])
    rescue => e                 # should restrict
      Leader.logger.error("raised error at dispatch #{e}")
      conn.send_response(result: nil, error: [e])
    end
  end

  class Client
    def initialize(host: '127.0.0.1', port:)
      @host = host or raise ArgumentError
      @port = port or raise ArgumentError
    rescue ArgumentError => e
      Leader.logger.error("failed when initilize client object #{e}")
      exit(1)
    end

    def attach(loop)
      loop.attach(connection)
    end

    def send(name)
      connection.send_request(name)
    end

    def connection
      @connection ||= Leader::ClientConnection.connect(@host, @port)
    end
  end
end
