require 'cool.io'
require 'json'

module Leader
  class BaseConnection < Cool.io::TCPSocket
    def on_read(data)
      Leader.logger.debug("#{self} #{remote_addr}:#{remote_port} read data")
      read_message(data)
    end

    def on_connect
      Leader.logger.debug("#{self} #{remote_addr}:#{remote_port} connected")
    end

    def on_close
      Leader.logger.debug("#{self} #{remote_addr}:#{remote_port} disconnected")
    end

    private

    def send_data(data)
      d = data.to_json
      Leader.logger.debug("#{self} #{remote_addr}:#{remote_port} send data #{d}")
      write d
    end

    def read_message(data)
      d = JSON.parse(data)
      yield(d)
    rescue => e
      Leader.logger.error("#{self} raised error at read_message : #{e}")
    end
  end

  class ServerConnection < BaseConnection
    def initialize(io, server)
      super(io)
      @server = server
    end

    def on_response(result, err)
      @server.on_response(self, result, err)
    end

    private

    def read_message(data)
      super(data) do |d|
        on_request(d['method'], d['params'] || [])
      end
    end

    def on_request(method_name, params)
      Leader.logger.debug("#{self} #{remote_addr}:#{remote_port} requested")
      @server.on_request(self, method_name, params)
    end
  end

  class ClientConnection < BaseConnection
    def send_request(name)
      d = { method: name, params: [] }
      send_data(d)
    end

    def on_resolve_failed
      Leader.logger.error("DNS resolve failed")
    end

    def on_connect_failed
      Leader.logger.error("connect failed, meaning our connection to their port was rejected")
    end

    private

    def on_read(data)
      super do |d|
        on_response(d['method'], d['params'])
        close
      end
    end
  end
end
