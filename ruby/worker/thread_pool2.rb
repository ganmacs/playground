require_relative 'jobs'
require_relative 'installer'
require 'thread'

module Worker
  class SimpleThreadPool
    def initialize(size, &block)
      @que = Queue.new
      @size = size
      @func = block
    end

    def enq(obj)
      @que.enq obj
    end

    def stop
      @threads.each(&:join)
    end

    def process
      Array.new(@size) do |i|
        Thread.start { _process(i) }
      end.each(&:join)
    end

    private

    def _process(i)
      while (job = @que.deq(true))
        @func.call(job, i)
      end
    rescue ThreadError
      Thread.exit
    end
  end
end

class ThreadInstaller2 < Installer
  private

  def enqueue
    @gems.each do |g|
      worker_pool.enq g
    end
  end

  def process
    worker_pool.process
  end

  def worker_pool
    @worker_pool ||= Worker::SimpleThreadPool.new(@size) do |gem, worker_num|
      gem.do_something_heavy_job(worker_num)
    end
  end
end

gems = JobsGenrator.call
ThreadInstaller2.new(3, gems).install!
