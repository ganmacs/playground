class WorkerManager
  def initialize(size)
    @size = size
    @workers = create_workers
  end

  def stop
    $log.info "Stoping workers #{@workers.map(&:pid)}"
    @workers.each(&:stop)
  end

  def run_with_worker
    @workers.map { |worker|
      Thread.new(worker) do |w|
        yield(w)
      end
    }.each(&:join)
  end

  def create_workers
    Array.new(@size) do |i|
      create_worker(i)
    end
  end

  def create_worker(i)
    Worker.create(i) do |read_io, write_io|
      heart_beat(read_io, write_io)
    end
  end

  def heart_beat(c_read, c_write)
    loop do
      v = c_read.gets
      v.chomp!
      c_write.puts(v + '+ack')
    end
  rescue SignalException
    $log.warn 'signal execption'
  end
end
