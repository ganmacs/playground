require 'ostruct'
require 'thread'

class Worker
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

class HeavyTask
  def self.call
    new.call
  end

  def call
    enqueue
    process
  end

  private

  def gems
    @gems ||= %w(rake bundler itamae specinfra kaminari rubocop).map do |n|
      OpenStruct.new(name: n, installed: false)
    end
  end

  def enqueue
    gems.each do |g|
      worker_pool.enq g
    end
  end

  def process
    process_gem until gems.all?(&:installed)
  ensure
    worker_pool && worker_pool.stop
  end

  def process_gem
    gem = worker_pool.deq
    gem.installed = true
  end

  def worker_pool
    @worker_pool ||= Worker.new(1) do |gem, worker_num|
      gem.tap do
        puts "START: #{gem.name} in #{worker_num}"
        a = 10000000.times.reduce(0) do |a, e|
          a + e
        end
        puts "FINISH: #{gem.name} in #{worker_num} #{a}"
      end
    end
  end
end

HeavyTask.call
