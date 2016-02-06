class Worker
  def initialize(size = 1)
    @request_queue = Queue.new
    @response_queue = Queue.new
    @thread = Array(size) do |i|
      Thread.start { process(i) }
    end
  end

  def enq(job)
    @response_queue.enq job
  end

  def deq
    @response_queue.deq
  end

  def process(i)
    job = @request_queue.deq
    @response_queue.enq job.call(i)
  end
end

worker_pool = Workder.new(3)
