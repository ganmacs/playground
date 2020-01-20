module BidiChannel
  class Receiver
    DATA_LENGHT_HEADER_SIZE = 4

    def initialize(channel, logger:)
      @channel = channel
      @inner = channel.channel_for_reader
      @buffer = +''.b
      @logger = logger
    end

    attr_reader :inner

    def recv(recv_size = 1024)
      ret = parse(@buffer)
      return ret if ret

      r, _ = IO.select([@inner], [], [])
      data = r.first.read_nonblock(recv_size, nil, exception: false)

      case data
      when nil
      # nil means EOF
      when :wait_readable
      # nothing
      else
        @buffer += data
      end

      if @buffer.empty?
        return nil
      end

      parse(@buffer)
    end

    def close
      @channel.close
    end

    private

    # message must be follow below
    # | data length (4bytes) | data |
    #
    def parse(data)
      if data.bytesize < DATA_LENGHT_HEADER_SIZE
        return nil
      end

      sizebuf = data.slice(0, DATA_LENGHT_HEADER_SIZE)
      unless sizebuf.size == DATA_LENGHT_HEADER_SIZE
        return nil
      end

      size = sizebuf.unpack('N').first

      ret = data.slice(4, size)
      if ret.bytesize == size
        data.slice!(0, DATA_LENGHT_HEADER_SIZE + size )
      else
        nil
      end
    end
  end
end
