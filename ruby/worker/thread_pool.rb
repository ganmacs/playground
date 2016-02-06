require 'thread'

module Worker
  class ThreadPool
    def initialize(size = 1, &block)
      @request_queue = Queue.new
      @response_queue = Queue.new
      @func = block
      @threads = Array.new(size) do |i|
        Thread.start { process(i) }
      end
    end

    def enq(obj)
      @request_queue.enq obj
    end

    def deq
      @response_queue.deq
    end

    def stop
      @threads.each { @request_queue.enq :halt_msg }
      @threads.each(&:join)
    end

    private

    def process(i)
      loop do
        obj = @request_queue.deq
        break if obj == :halt_msg
        @response_queue.enq @func.call(obj, i)
      end
    end
  end
end
