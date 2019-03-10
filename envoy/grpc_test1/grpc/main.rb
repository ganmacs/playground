require 'logger'
require 'grpc'
require 'grpc/health/checker'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

health_checker = Grpc::Health::Checker.new
health_checker.add_status('test-app', Grpc::Health::V1::HealthCheckResponse::ServingStatus::SERVING)

s = GRPC::RpcServer.new
s.add_http2_port('127.0.0.1:8000', :this_port_is_insecure)
s.handle(health_checker)

finish = Queue.new

stop_server_thread = Thread.new do
  reason = finish.pop
  GRPC.logger.info("Stopping... #{reason}")
  s.stop
end

trap('INT') do
  GRPC.logger.info('Trapping SIGINT')
  finish.push(:int)
end

trap('TERM') do
  GRPC.logger.info('Trapping SIGTERM')
  finish.push(:term)
end

s.run_till_terminated
stop_server_thread.join
