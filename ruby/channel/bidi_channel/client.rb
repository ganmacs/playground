require 'bidi_channel/receiver'
require 'bidi_channel/sender'

module BidiChannel
  class Client
    def initialize(logger:)
      @channels = {}
      @logger = logger
    end

    def setup_connection(name)
      n = BidiChannel::FifoChannel.generate_name("worker#{name}")
      channel = BidiChannel::FifoChannel.new_with_base_dir(n)
      channel.build
      @receiver = BidiChannel::Receiver.new(channel, logger: @logger)

      # c = BidiChannel::FifoChannel.new_f
      c = BidiChannel::FifoChannel.build_from_env_var
      @sender = BidiChannel::Sender.new(c, logger: @logger)

      send(channel.name)
    end

    def send(data, skip_recv = true)
      @sender.write(data)
      unless skip_recv          # XXX
        @receiver.recv
      end
    end

    def finish
      @sender.close
    end
  end
end
