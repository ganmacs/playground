require 'logger'
require 'logger'
require 'grpc'
require 'pry'
$LOAD_PATH.unshift File.expand_path('.')

require_relative 'helloworld_services_pb'

# module RubyLogger
#   def logger
#     Logger.new(STDOUT, level: :debug)
#   end
# end
# GRPC.extend(RubyLogger)

stub = Helloworld::Greeter::Stub.new('localhost:50051', :this_channel_is_insecure)
100000.times {
  message = stub.say_hello(Helloworld::HelloRequest.new(name: 'ganmacs'))
}
# p "Greeting: #{message}"
