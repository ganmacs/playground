require 'logger'
require 'grpc'
require 'grpc/health/checker'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

stub = Grpc::Health::V1::Health::Stub.new('127.0.0.1:8000', :this_channel_is_insecure)

count = 0
2.times do
  begin
    p stub.check(Grpc::Health::V1::HealthCheckRequest.new(service: 'test-app'), deadline: Time.now.to_f + 0)
    count += 1
  rescue => e
    p e
  end
end

puts count
