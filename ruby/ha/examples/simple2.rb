require "bundler/setup"
require "hagrpc"

require 'serverengine'
require "socket"
require "logger"

# Server module controls the parent process
module MyServer
  def before_run

    p config[:bind]
    p config[:port]
    @sock = ::TCPServer.new(config[:bind], config[:port])
  end

  attr_reader :sock
end

# Worker module controls child processes
module MyWorker
  def run
    until @stop
      # you should use Cool.io or EventMachine actually
      c = server.sock.accept
      c.write "Awesome work!"
      c.close
    end
  end

  def stop
    @stop = true
  end
end

se = ServerEngine.create(
  MyServer,
  MyWorker,
  # daemonize: true,
  log: STDOUT,
  pid_path: 'myserver.pid',
  worker_type: 'process',
  workers: 2,
  bind: '0.0.0.0',
  port: 3000,
  logger: Logger.new(STDOUT, level: 'debug')
)
se.run
