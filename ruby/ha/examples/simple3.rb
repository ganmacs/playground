require "bundler/setup"
require "hagrpc"

require 'serverengine'
require 'logger'
require "socket"

require_relative './checker.rb'

require 'cool.io'
HOST = 'localhost'
PORT = 3000

class EchoServerConnection < Cool.io::TCPSocket
  def initialize(sock, outs)
    @adder = outs
  end

  def on_connect
    puts "#{remote_addr}:#{remote_port} connected"
  end

  def on_close
    puts "#{remote_addr}:#{remote_port} disconnected"
  end

  def on_read(data)
    puts nil, '<============================================================ OUTPUT START HERE'
    @outs ||= @adders.map do |addr, port|
      ::TCPSocket.new(addr, port)
    end

    puts nil, '<============================================================ OUTPUT START HERE'

    out = @outs.pop

    Thread.new do
      begin
        out.write(data)
        write out.gets
      ensure
        @outs.enq(out)
      end
    end
  end
end

# Server module controls the parent process
module MyServer
  def before_run
    @sock1 = ['127.0.0.1', '8000']
    @sock2 = ['127.0.0.1', '8001']
    # @sock3 = ['127.0.0.1', '8002']
    @socks = [@sock1]

    @loop = Coolio::Loop.new
    server = Cool.io::TCPServer.new(config[:bind], config[:port], ::EchoServerConnection, @socks)
    server.attach(@loop)

    @thread = Thread.new do
      @loop.run(0.5)
    end
  end

  attr_reader :thread, :sock
end

# Worker module controls child processes
module MyWorker
  def run
    s = TCPServer.new '127.0.0.1', "800#{worker_id}"

    until @stop
      v = s.accept.gets
      puts nil, '<=======hey===================================================== OUTPUT START HERE'
      p v
      puts '<============================================================ OUTPUT CLOSE HERE', nil
      s.close
    end
  end

  def stop
    @stop = true
  end
end

se = ServerEngine.create(
  MyServer,
  MyWorker, {
    # daemonize: true,
    log: STDOUT,
    pid_path: 'myserver.pid',
    worker_type: 'process',
    workers: 2,
    # bind: '127.0.0.1',
    bind: '0.0.0.0',
    port: 3000,
    logger: Logger.new($stdout),
  })

se.run
