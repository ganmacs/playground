module Eve
  class SafeBuffer
    def initialize
      @mutex = Mutex.new
      @buffer = ""
    end

    def to_data
      @mutex.synchronize do
        @buffer
      end
    end

    def flash
      return false unless buffered?
      write @buffer
      reset_buffer
      true
    end

    def add(data)
      v = data.to_s           # is #to_s ok?
      @mutex.synchronize do
        @buffer << v
      end
    end

    def reset
      @mutex.synchronize do
        @buffer = ""
      end
    end

    def buffered?
      @mutex.synchronize do
        !@buffer.empty?
      end
    end
  end
end
