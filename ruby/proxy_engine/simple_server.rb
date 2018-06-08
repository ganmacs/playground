require 'webrick'
require 'logger'

class SimpleServer
  def initialize(addr, port, logger, id)
    @addr = addr
    @port = port
    @logger = logger
    @server = start_server
    @id = id

    install_singnal_handle
    setup
  end

  def start_server
    @logger.info("listen #{@addr}:#{@port}")
    WEBrick::HTTPServer.new(Port: @port, BindAddress: @addr)
  end

  def setup
    @server.mount_proc('/') do |req, res|
      @logger.info(req.request_line)
      @logger.info(req.header)
      @logger.info("\n#{req.body}") if req.body

      res.status = 200
      res['Content-Type'] = 'text/html'
      res.body = "Hello from worker #{@id}\n"
    end
  end

  def install_singnal_handle
    Signal.trap(:INT) { @server.shutdown }
  end

  def run
    @server.start
  end

  def stop
    @server.stop
  end
end
