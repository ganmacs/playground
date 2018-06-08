require 'serverengine'
require_relative './rproxy'
require_relative './simple_server'

PORT = 3000
ADDR = '127.0.0.1'
$logger = Logger.new(STDOUT)

module MyServer
  attr_reader :socket_manager_path

  def before_run
    bc = RoundRobin.new([ { addr: '127.0.0.1', port: 8000 }, { addr: '127.0.0.1', port: 8001 }])
    @lb = LoadBlancer.new(ADDR, PORT, bc, $logger)
    @t = Thread.new do |x|
      @lb.run
    end
  end

  def after_run
    @lb.stop
    @t.join
  end
end

module MyWorker
  def run
    @server = SimpleServer.new('127.0.0.1', 8000 + worker_id, $logger, worker_id)
    @server.run
  end

  def stop
    @server.stop
  end
end

se = ServerEngine.create(
  MyServer,
  MyWorker,
  daemonize: false,
  daemon_process_name: 'mydaemon',
  supervisor: false,
  log: 'myserver.log',
  pid_path: 'myserver.pid',
  worker_type: 'process',
  workers: 2,
  stop_immediately_at_unrecoverable_exit: true,
)

se.run
