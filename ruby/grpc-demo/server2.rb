require 'logger'
require 'grpc'
require 'grpc/health/v1/health_services_pb'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

class MyService < Grpc::Health::V1::Health::Service
  # overwrite
  def check(req, _call)
    sleep 10
    Grpc::Health::V1::HealthCheckResponse.new(status: Grpc::Health::V1::HealthCheckResponse::ServingStatus::SERVING)
  end
end

health_checker = MyService.new
s = GRPC::RpcServer.new(pool_size: 1)
s.add_http2_port('127.0.0.1:50051', :this_port_is_insecure)
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
