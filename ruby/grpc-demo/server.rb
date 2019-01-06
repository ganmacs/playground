$LOAD_PATH.unshift File.expand_path('.')

require 'logger'
require 'grpc'
require 'helloworld_services_pb'
require 'pry'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

class I < GRPC::ServerInterceptor
  def request_response(request: nil, call: nil, method: nil)

    # call.metadata['a'] = '10'
    # call.send_metadata['b'] = 11
    call.output_metadata['c'] = '12'
    call.metadata_to_send['d'] = '3'
    p call.metadata
    # binding.pry
    yield
  end
end

class GreeterServer < Helloworld::Greeter::Service
  def say_hello(req, _call)
    GRPC.logger.info(req)
    Helloworld::HelloReply.new(message: "Hello #{req.name}")
  end
end

s = GRPC::RpcServer.new(interceptors: [I.new])
s.add_http2_port('127.0.0.1:50051', :this_port_is_insecure)
s.handle(GreeterServer.new)
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
