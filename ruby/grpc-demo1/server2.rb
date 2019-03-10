require 'logger'
require 'grpc'
require 'grpc/health/v1/health_services_pb'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

module Grpc
  module Health
    class Checker < V1::Health::Service
      def check(req, _call)
        V1::HealthCheckResponse.new(status: V1::HealthCheckResponse::ServingStatus::SERVING).tap do
          # sleep(1)
        end
      end
    end
  end
end

s = GRPC::RpcServer.new
s.add_http2_port('127.0.0.1:3000', :this_port_is_insecure)
s.handle(Grpc::Health::Checker.new)
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
