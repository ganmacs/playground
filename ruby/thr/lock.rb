require 'benchmark'
require 'thread'

class State
  def initialize
    @queue = Queue.new
    @new_lock = Mutex.new
  end

  def env
  end
end
# a = State.new

# N = 3
# threads = N.times.map do |x|
#   Thread.start do
#     sleep 1
#     puts x
#   end
# end

# threads.map(&:join)


def fib(n)
  if n <= 2
    1
  else
    fib(n - 2) + fib(n - 1)
  end
end

class A
  attr_reader :queue

  def initialize(min = 20, max = 30)
    @queue = Queue.new
    @max = max
    @min = min
  end

  def call
    [*@min..@max].map do |x|
      @queue.push fib(x)
    end
  end

  def call_t
    thrs = [*@min..@max].map do |x|
      Thread.start do
        @queue.push fib(x)
      end
    end
    thrs.map(&:join)
  end
end

a = A.new
b = A.new
COUNT = 10

Benchmark.bm(10) do |r|
  r.report 'sequecal' do
    COUNT.times do |x|
      a.call
    end
  end

  r.report 'thread' do
    COUNT.times do |x|
      b.call_t
    end
  end
end

p a.queue
p b.queue
