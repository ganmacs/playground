require_relative 'jobs'

module Worker
  class ThreadPoolDeps
    def initialize(size = 1, &block)
      @request_queue = Queue.new
      @response_queue = Queue.new
      @func = block
      @threads = Array.new(size) do |i|
        Thread.start { process(i) }
      end
      trap('INT') { abort_threads }
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

    def abort_threads
      @threads.each(&:exit)
      exit 1
    end
  end
end

class DepsInstaller < Installer
  private

  def enqueue
    @gems.each do |g|
      worker_pool.enq g
    end
  end

  def process
    process_gem until @gems.all?(&:installed?)
  ensure
    worker_pool.stop
  end

  def process_gem
    gem = worker_pool.deq
    gem.installed = true
  end

  def worker_pool
    @worker_pool ||= Worker::ThreadPoolDeps.new(@size) do |gem, worker_num|
      gem.do_something_heavy_job(worker_num)
    end
  end
end

gems = JobsGenrator.call
ThreadInstaller.new(4, gems).install!
