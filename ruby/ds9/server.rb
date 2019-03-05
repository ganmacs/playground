require 'ds9'
require 'objspace'
require 'socket'

module Hoge
  module IOEvents
    def initialize(sock)
      @sock = sock
      super()
    end

    def send_event(string)
      @sock.write_nonblock(string)
    end

    def recv_event(length)
      case data = @sock.read_nonblock(length, nil, exception: false)
      when :wait_readable
        DS9::ERR_WOULDBLOCK
      when nil
        DS9::ERR_EOF
      else
        data
      end
    rescue IOError
      DS9::ERR_EOF
    end

    def run
      while want_read? || want_write?
        if want_write?
          send
        end

        if want_read?
          receive
        end
      end
    rescue DS9::Exception => _
      # p e
    end
  end

  class Server < DS9::Server
    include IOEvents

    def initialize(sock)
      @streams = {}
      super(sock)

      submit_settings([])
    end

    def on_begin_headers(frame)
      @streams[frame.stream_id] = ''
    end

    def on_stream_close(id, error_code)
      @streams.delete(id)

      print_mem
      true
    end

    def on_frame_recv(frame)
      unless (frame.data? || frame.headers?) && frame.end_stream?
        return
      end

      submit_response(frame.stream_id, ':status' => '200', 'content-type' => 'application/grpc')
    end

    def on_data_source_read(stream_id, length)
      data = @streams[stream_id].slice(0, length)

      if data.empty?
        submit_trailer(stream_id, 'grpc-status' => '0', 'grpc-message' => 'test')
        false
      else
        @streams[stream_id].slice!(0, length)
        data
      end
    end

    def on_data_chunk_recv(id, data, flags)
      @streams[id] << data
    end

    def print_mem
      @i ||= 0
      if (@i % 50) == 0
        GC.start
        puts("memsize_of_all: #{ObjectSpace.memsize_of_all / 1000} KB, rss: #{`ps -o rss= #{Process.pid}`.chomp} KB")
      end
      @i += 1
    end
  end
end

sock = TCPServer.new(50051)
loop do
  conn = sock.accept
  Hoge::Server.new(conn).run
end
