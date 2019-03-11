require 'logger'
require 'pry'
require 'grpc'
require 'grpc/health/v1/health_services_pb'
require_relative 'my_server'

module RubyLogger
  def logger
    Logger.new(STDOUT, level: :debug)
  end
end
GRPC.extend(RubyLogger)

health_checker = MyService.new
s = GRPC::RpcServer.new(pool_size: 1)
s.add_http2_port('127.0.0.1:50051', :this_port_is_insecure)

s.handle(health_checker)

finish = Queue.new

stop_server_thread = Thread.new do
  reason = finish.pop
  GRPC.logger.info("Stopping... #{reason}")
  s.stop
end

# trap('INT') do
#   GRPC.logger.info('Trapping SIGINT')
#   finish.push(:int)
# end

# trap('TERM') do
#   GRPC.logger.info('Trapping SIGTERM')
#   finish.push(:term)
# end

trap(:USR2) {
  Thread.new do
    p 'load my_server'

    load('./my_server.rb')

    ms = MyService.new
    state = s.instance_variable_get(:@running_state)
    # colud be race
    begin
      s.instance_variable_set(:@running_state, :not_started)
      s.instance_eval do
        @rpc_handlers.clear
        @rpc_descs.clear
      end
      s.handle(ms)
    ensure
      s.instance_variable_set(:@running_state, state)
    end
  end.join
}

s.run_till_terminated
stop_server_thread.join
