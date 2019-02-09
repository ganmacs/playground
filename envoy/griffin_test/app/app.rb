require 'google/protobuf'
require 'grpc'

Google::Protobuf::DescriptorPool.generated_pool.build do
  add_message "helloworld.HelloRequest" do
    optional :name, :string, 1
  end
  add_message "helloworld.HelloReply" do
    optional :message, :string, 1
  end
end

module Helloworld
  HelloRequest = Google::Protobuf::DescriptorPool.generated_pool.lookup("helloworld.HelloRequest").msgclass
  HelloReply = Google::Protobuf::DescriptorPool.generated_pool.lookup("helloworld.HelloReply").msgclass
end

module Helloworld
  module Greeter
    class Service

      include GRPC::GenericService

      self.marshal_class_method = :encode
      self.unmarshal_class_method = :decode
      self.service_name = 'helloworld.Greeter'

      rpc :SayHello, HelloRequest, HelloReply
    end

    Stub = Service.rpc_stub_class
  end
end

# ------

require 'griffin'
require 'griffin/interceptors/server/worker_killer_interceptor'

class GreeterServer < Helloworld::Greeter::Service
  def say_hello(hello_req, _unused_call)
    Helloworld::HelloReply.new(message: "Hello #{hello_req.name}")
  end
end

Griffin::Server.configure do |c|
  c.bind '0.0.0.0'

  c.port 8080

  c.services GreeterServer.new

  c.interceptors [Griffin::Interceptors::Server::WorkerKillerInterceptor.new]

  c.workers 2

  c.connection_size 1, 2
end

Griffin::Server.run
