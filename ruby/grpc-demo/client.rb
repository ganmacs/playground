require 'logger'
require 'logger'
require 'grpc'
require 'pry'
$LOAD_PATH.unshift File.expand_path('.')

require_relative 'helloworld_services_pb'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

class I < GRPC::ClientInterceptor
  def request_response(request: nil, call: nil, method: nil, metadata: nil)
    puts nil, '<============================================================ OUTPUT START HERE'
    p metadata
    puts '<============================================================ OUTPUT CLOSE HERE', nil
    p metadata['b'] = '100'
    # metadata['a'] = '10'
    # call.metadata['b'] = 'a'
    # call.metadata['a'] = '10'
    # call.send_metadata['b'] = 11
    # call.output_metadata['c'] = '12'
    # binding.pry
    yield
  end
end

stub = Helloworld::Greeter::Stub.new('localhost:50051', :this_channel_is_insecure, interceptors: [I.new])
message = stub.say_hello(Helloworld::HelloRequest.new(name: 'ganmacs'), metadata: {'hoge' => '1'}, return_op: true)
p "Greeting: #{message}"
p message.metadata
