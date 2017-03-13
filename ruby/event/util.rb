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

class Ticker
  def self.start(duraiton, &block)
    new.start(duraiton, block)
  end

  def start(duraiton, block)
    t = Thread.current
    @t = Thread.new do
      loop do
        begin
          block.call
          sleep duraiton
        rescue => e
          t.raise(e)            # ok?
          break
        end
      end
    end
  end

  def stop
    @t.kill
  end
end

class Future
  def initialize(conn, &block)
    @conn = conn
    @set = false
    @result = nil
    @err = nil
    @hook = block
    @thread = Thread.current
  end

  def get
    join
    return @hook.call(@result, @err) if @hook

    if @err
      @err
    else
      @result
    end
  end

  def set(data, err = nil)
    @set = true
    @result = data
    @err = err
    @thread.wakeup
  end

  private

  def join
    unless @set
      sleep(10)
      raise 'Timeout' unless @set
    end
  end
end
