require_relative 'thread_pool'
require_relative 'jobs'

class ThreadInstaller
  def self.call(gems)
    new(gems).call
  end

  def initialize(gems)
    @gems = gems
  end

  def call
    enqueue
    process
  end

  private

  def enqueue
    @gems.each do |g|
      worker_pool.enq g
    end
  end

  def process
    process_gem until @gems.all?(&:installed?)
  ensure
    worker_pool && worker_pool.stop
  end

  def process_gem
    gem = worker_pool.deq
    gem.installed = true
  end

  def worker_pool
    @worker_pool ||= Worker::ThreadPool.new(1) do |gem, worker_num|
      gem.do_something_heavy_job(worker_num)
    end
  end
end

gems = JobsGenrator.call
ThreadInstaller.call(gems)
