# frozen_string_literal: true

require 'griffin'
require 'grpc/health/v1/health_services_pb'

module Grpc
  module Health
    class Checker < V1::Health::Service
      def check(req, _call)
        V1::HealthCheckResponse.new(status: V1::HealthCheckResponse::ServingStatus::SERVING)
      end
    end
  end
end

Griffin::Server.configure do |c|
  c.bind '0.0.0.0'

  c.services Grpc::Health::Checker.new

  c.workers 1
end

Griffin::Server.run
