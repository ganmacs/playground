class Worker
  attr_reader :pid, :running

  def self.create(name)
    c_read, p_write = IO.pipe
    p_read, c_write = IO.pipe

    pid = Process.fork do
      begin
        p_read.close
        p_write.close

        yield(c_read, c_write)
      ensure
        c_read.close
        c_write.close
      end
    end

    c_read.close
    c_write.close

    Worker.new(pid, p_read, p_write, name)
  end

  def initialize(pid, read_io, write_io, name)
    @name = name
    @read_io = read_io
    @write_io = write_io
    @pid = pid
    @running = true
  end

  def stop
    $log.info "Stoping worker #{@name}"
    @running = false
    Process.kill(:KILL, @pid)
    @read_io.close
    @write_io.close
  end

  def heart_beat(v)
    @write_io.puts(v)
    ret = @read_io.gets
    ret.chomp!

    if !ret.empty? && ret == (v + '+ack')
      $log.info "OK #{@pid} --- #{@name}"
    else
      raise v
    end
  end
end
