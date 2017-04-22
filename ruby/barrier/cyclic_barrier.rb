class CyclicBarrier
  def initialize(n)
    @n = n
    @wait_count = 0
    @mutex = Mutex.new
    @cv = ConditionVariable.new
  end

  def wait
    @mutex.synchronize do
      @wait_count += 1

      if @wait_count == @n
        @cv.broadcast
      else
        @cv.wait(@mutex)
      end
    end
  end
end

class Runner
  def initialize(n)
    @n = n
    @cb = CyclicBarrier.new(n)
    @queue = Queue.new
  end

  def run
    (@n - 1).times.map do |i|
      Thread.start(i + 1) { |j| process(j) }
    end

    reduce_process
  end

  private

  def reduce_process
    puts "[Wait] reduce process"
    @cb.wait
    puts "[Start] reduce process"

    result = 0
    until @queue.empty?
      result += @queue.pop
    end

    puts "[Done] result is #{result}"
  end

  def process(i)
    puts "[Start] process #{i}"

    sleep(i)
    @queue << i

    puts "[Wait] process #{i}"
    @cb.wait
  end
end

Runner.new(4).run
