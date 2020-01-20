require 'bidi_channel/receiver'
require 'bidi_channel/sender'
require 'bidi_channel/fifo_channel'

module BidiChannel
  class Server
    def initialize(logger:)
      @channels = {}
      @logger = logger
      @r, @w = IO.pipe
    end

    def setup_connection
      channel = BidiChannel::FifoChannel.build_server
      receiver = BidiChannel::Receiver.new(channel, logger: @logger)

      client_path = receiver.recv
      @logger.info("receive: #{client_path}")

      # sleep 0.1 until (client_path = receiver.recv) # blocking
      c = BidiChannel::FifoChannel.new(client_path)
      sender = BidiChannel::Sender.new(c, logger: @logger)
      @channels[receiver] = sender

      @logger.info("success: #{client_path}")
    end

    def recv(timeout = nil)
      finish = false
      until finish
        rs, _ = IO.select(@channels.keys.map(&:inner) + [@r], [], [], timeout)
        rs.each do |r|
          if r == @r
            v = @r.read(1)
            if v == 0
              @logger.info('finish!')
              finish = true
              break
            end
          end

          r = @channels.keys.find { |e| e.inner == r }
          if (v = r.recv)
            yield(v, @channels[r]) # worker?
          end
        end
      end
    end

    def finish
      @w.write(0)
      # broadcast("finish")
    end

    def broadcast(data)
      @channels.values.each do |w|
        w.send(data)
      end
    end
  end
end
