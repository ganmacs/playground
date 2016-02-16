# http://qiita.com/yuroyoro/items/92c5bc864fa9c05127a9

# 子プロセスを管理するWorkerクラス
class Worker
  attr_reader :pid

  def initialize(&block)
    @child_read, @parent_write = create_pipe # 親から子へのpipe
    @parent_read, @child_write = create_pipe # 子から親へのpipe
    @block = block # forkして実行する処理
  end

  def create_pipe
    # Marshal.dumpの結果はASCII-8BITなのでpipeのエンコーディングもあわせる
    IO.pipe.map{|pipe| pipe.tap{|_| _.set_encoding("ASCII-8BIT", "ASCII-8BIT") } }
  end

  # 子プロセスの起動処理
  def run
    @pid = fork do # forkする

      # 子で使わないpipeは閉じる
      @parent_read.close
      @parent_write.close

      # 親プロセスに起動終了を伝える
      write_to_parent(:ready)

      loop do
        # 親からの依頼待ち
        args = read_from_parent

        # stopが飛んで来たらloopを抜けて子プロセスを終了させる
        break if args == :stop

        # 処理を実行する
        result = @block.call(*args)

        # 結果をpipeに書き込んで完了を親に伝える
        write_object(result, @child_write)
      end

      @child_read.close
      @child_write.close
    end

    wait_after_fork if @pid
  end

  # 子プロセスに処理を行わせる
  def execute(*msg)
    write_to_child(msg)

    Thread.new { read_from_child } # Threadを起こして子からpipeに書き込まれるのを待つ
  end

  def stop
    return unless alive?

    # 子を終了させる
    write_to_child(:stop)

    # waitpidで子プロセスを回収する
    Process.wait(@pid)
  end

  def alive?
    Process.kill(0, @pid)
    true
  rescue Errno::ESRCH
    false
  end

  def write_object(obj, write)
    # RubyオブジェクトをMarshalしてpipeに書き込む
    # 改行をデリミタにする
    data = Marshal.dump(obj).gsub("\n", '\n') + "\n"
    write.write data
  end

  def read_object(read)
    # pipeから読み込んだデータをRubyオブジェクトに復元する
    data = read.gets
    Marshal.load(data.chomp.gsub('\n', "\n"))
  end

  def read_from_child
    read_object(@parent_read)
  end

  def write_to_child(obj)
    write_object(obj, @parent_write)
  end

  def read_from_parent
    read_object(@child_read)
  end

  def write_to_parent(obj)
    write_object(obj, @child_write)
  end

  def wait_after_fork
    @child_read.close
    @child_write.close

    install_exit_handler
    install_signal_handler

    # 子から起動完了が通知されるまで待つ
    Thread.new {
      result = read_from_child
      raise "Failed to start worker pid #{ @pid }" unless result == :ready
      result
    }
  end

  def install_exit_handler
    # Kernel#at_exitで子を回収
    at_exit do
      next unless alive?
      begin
        Process.kill("KILL", @pid)
        Process.wait(@pid)
      rescue Errno::ESRCH
      # noop
      rescue => e
        puts "error at_exit: #{ e }"
        raise e
      end
    end
  end

  def install_signal_handler
    # 親のSIGINT, SIGQUITは子プロセスにも転送する
    [:INT, :QUIT].each do |signal|
      old_handler = Signal.trap(signal) {
        Process.kill(signal, @pid)
        Process.wait(@pid)
        old_handler.call
      }
    end
  end
end

# 4プロセス分Worker作成
workers = Array.new(4) do |x|
  Worker.new { puts "execute #{x}" }
end

# Workerプロセス起動
workers.map(&:run).each(&:join)

# 処理開始
threads = workers.map{|worker|
  worker.execute(*args)
}

# Workerが終わるまで待ち合わせ
threads.each(&:join)

# Workerプロセスを停止
workers.each(&:stop)
