require 'logger'
require 'logger'
require 'grpc'
require_relative 'helloworld_services_pb'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

stub = Helloworld::Greeter::Stub.new('localhost:8000', :this_channel_is_insecure)
message = stub.say_hello(Helloworld::HelloRequest.new(name: 'ganmacs')).message
p "Greeting: #{message}"
