class Engine
  DEFAULT_WORKER_SIZE = 5

  def initialize(**options)
    @worker_size = options.fetch(:worker_size, DEFAULT_WORKER_SIZE)
    @wm = WorkerManager.new(@worker_size)

    install_singanl_handlers(@wm)
  end

  def run
    $log.info 'Start engine'
    @wm.run_with_worker do |worker|
      while worker.running
        begin
          worker.heart_beat(Time.now.to_s)
        rescue => e
          $log.warn "#{e} in Engine#run"
        end
      end
    end
  end

  def install_singanl_handlers(pm)
    trap :INT do
      Thread.new do
        $log.warn 'Recieved SIGINT, kill all workers'
        pm.stop
      end.join
    end

    trap :TERM do
      pm.stop
      puts 'recieve SIGTERM'
    end
  end
end
