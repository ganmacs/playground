module BidiChannel
  class Sender
    def initialize(channel, logger:)
      @channel = channel
      @logger = logger
    end

    def write(data)
      @logger.debug("write data: #{data}")
      inner.write(format_data(data))
      inner.flush
    end

    def close
      @channel.close
    end

    private

    # message must be follow below
    # | data length (4bytes) | data |
    def format_data(data)
      size = [data.bytesize].pack('N')
      size + data
    end

    def inner
      # Fifo file can be block when reader does not open the fiel
      @channel.channel_for_writer
    end
  end
end
