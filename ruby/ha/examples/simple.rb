require "bundler/setup"
require "hagrpc"

require 'serverengine'
require "socket"

require_relative './checker.rb'

require 'cool.io'
HOST = 'localhost'
PORT = 3000

# Server module controls the parent process
module MyServer
  def before_run
    server = Cool.io::TCPServer.new(HOST, PORT, EchoServerConnection)
    server.attach(Cool.io::Loop.default)
  end

  attr_reader :sock
end

# Worker module controls child processes
module MyWorker
  def run
    # server = GRPC::RpcServer.new
    # server.add_http2_port('0.0.0.0:3000', :this_port_is_insecure)
    # health_checker = Grpc::Health::Checker.new
    # health_checker.add_status('test', Grpc::Health::V1::HealthCheckResponse::ServingStatus::SERVING)
    # server.handle(health_checker)
    # @sock = server
    # puts worker_id
    # server.sock.run_till_terminated
  end

  def stop
    server.sock.stop
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

class EchoServerConnection < Cool.io::TCPSocket
  def on_connect
    puts "#{remote_addr}:#{remote_port} connected"
  end

  def on_close
    puts "#{remote_addr}:#{remote_port} disconnected"
  end

  def on_read(data)
    write data
  end
end

class HAGrpc
  def initialize(options)
    @options = options
  end

end
