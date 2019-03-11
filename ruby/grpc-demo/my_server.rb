require 'grpc'
require 'grpc/health/v1/health_services_pb'

class MyService < Grpc::Health::V1::Health::Service
  # overwrite
  def check(req, _call)
    puts "aaa"
    Grpc::Health::V1::HealthCheckResponse.new(status: Grpc::Health::V1::HealthCheckResponse::ServingStatus::SERVING)
  end
end
