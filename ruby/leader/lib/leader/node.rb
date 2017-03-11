require 'leader/connection'
require 'leader/hander'

module Leader
  class Node
    DEFAULT_HOST = 'localhost'
    DEFAULT_PORT = 4321

    def initialize(host = ENV['LEADER_HOST'], port = ENV['LEADER_PORT'])
      @handler = Leader::Handler.new
      @host = host || DEFAULT_HOST
      @port = port || DEFAULT_PORT
    end

    def start
    end

    def attach
      @conn = Cool.io::TCPServer.new(@host, @port, Leader::Connection, self)
    end

    def on_request(conn, method_name, params)
      dispatch(method_name, params)
    end

    private

    def dispatch(method_name, params)
      @handler.send(method_name, *params)
    rescue => e                 # should restrict
      Leader.logger.error("raised error at dispatch #{e}")
    end
  end
end
