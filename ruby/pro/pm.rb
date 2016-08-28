require 'logger'

$log = Logger.new($stdout)

class Worker
  attr_reader :pid, :running

  def initialize(pid, read_io, write_io)
    @read_io = read_io
    @write_io = write_io
    @pid = pid
    @running = true
  end

  def stop
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
      puts "ok #{self}"
    else
      raise v
    end
  end
end

class Manager
  attr_reader :worker

  def initialize(factory, n)
    @factory = factory
    @n = n
    @workers = Array.new(n).map do |i|
      create_worker(i)
    end
  end

  def stop
    puts "finish worker #{@workers.map(&:pid)}"
    @workers.each(&:stop)
  end

  def run_with_worker(&block)
    @workers.map { |worker|
      Thread.new(worker) { |w| block.call(w) }
    }.each(&:join)
  end

  def create_worker(i)
    c_read, p_write = IO.pipe
    p_read, c_write = IO.pipe

    pid = Process.fork do
      begin
        p_read.close
        p_write.close

        heart_beat(c_read, c_write)
      rescue => e
        puts 'finish'
      ensure
        c_read.close
        c_write.close
      end
    end

    c_read.close
    c_write.close

    Worker.new(pid, p_read, p_write)
  end

  def heart_beat(c_read, c_write)
    loop do
      v = c_read.gets
      v.chomp!
      c_write.puts(v + '+ack')
      sleep 0.1
    end
  rescue => e
    puts e
  end
end

class Server
  def initialize(n)
    @pm = Manager.new(self, n)
    @finish = false
    install_singanl_handlers(@pm)
  end

  def run
    exception = nil

    @pm.run_with_worker do |worker|
      begin
        until exception && !worker.running
          begin
            worker.heart_beat(Time.now.to_s)
            sleep 1
          rescue => e
            exception = e         # need lock?
          end
        end
      ensure
        worker.stop
      end
    end

    p exception if exception
  end

  private

  def install_singanl_handlers(pm)
    trap :INT do
      pm.stop
      puts 'sigint'
      exit 1
    end

    trap :TERM do
      pm.stop
      puts 'sigint'
    end
  end
end

Server.new(3).run
