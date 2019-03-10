require 'logger'
require 'grpc'
require_relative './checker'

module StdoutLogger
  def logger
    LOGGER
  end

  LOGGER = Logger.new(STDOUT)
end

GRPC.extend(StdoutLogger)

client = Grpc::Health::V1::Health::Stub.new(
  '127.0.0.1:8000',
  :this_channel_is_insecure,
  timeout: 10
)
req = Grpc::Health::V1::HealthCheckRequest.new(service: 'test')

@stop = false

GRPC.logger.info(" #{client.check(req).status}")
