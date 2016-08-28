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
    c_read, p_write = IO.pipe
    p_read, c_write = IO.pipe

    pid = Process.fork do
      begin
        p_read.close
        p_write.close

        heart_beat(c_read, c_write)
      ensure
        c_read.close
        c_write.close
      end
    end

    c_read.close
    c_write.close

    Worker.new(pid, p_read, p_write, i)
  end

  def heart_beat(c_read, c_write)
    begin
      loop do
        v = c_read.gets
        v.chomp!
        c_write.puts(v + '+ack')
      end
    rescue SignalException
      $log.warn "signal execption"
    end
  end
end
