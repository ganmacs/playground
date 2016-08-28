class Worker
  attr_reader :pid, :running

  def initialize(pid, read_io, write_io, i)
    @i = i
    @read_io = read_io
    @write_io = write_io
    @pid = pid
    @running = true
  end

  def stop
    $log.info "Stoping worker #{@i}"
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
      $log.info "OK #{@pid} --- #{@i}"
    else
      raise v
    end
  end
end
