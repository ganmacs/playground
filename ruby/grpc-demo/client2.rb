require 'logger'
require 'grpc'
require 'grpc/health/checker'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

stub = Grpc::Health::V1::Health::Stub.new('127.0.0.1:50051', :this_channel_is_insecure)
1000.times do
  10.times do
    p stub.check(Grpc::Health::V1::HealthCheckRequest.new(service: 'hoge'))
  end
end
# end.each(&:join)

sleep
