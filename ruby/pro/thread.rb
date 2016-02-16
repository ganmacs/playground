require 'open3'

def start_loop
  ts = []

  puts '==========start loop'

  1000.times do |i|
    puts 'start'

    ts << Thread.start(i) do
      Open3.capture3('sleep 1') # blocking
      p "finsh sleep #{i}"
    end

    puts 'end'
    sleep 1
  end

  puts '==========finish loop'

  ts.each(&:join)
end


def queue_start_loop
  q = Queue.new
  q1 = Queue.new

  puts '==========start loop'
  tps = Array.new(10) do |i|
    Thread.start do
      f = q1.deq
      f.call(i)
      q.enq "finish #{i}"
    end
  end

  10.times do
    puts 'start'

    q1.enq(->(x) { sleep x })

    unless q.empty?
      q.size.times do
        p q.deq
      end
    end

    puts 'end'
    sleep 1
  end

  puts '==========finish loop'

  p q.num_waiting

  tps.each(&:join)
end

# def process

# end

longstr = '0123456789' * 10000
read_pipe, write_pipe = IO.pipe

pid = fork do
  read_pipe.close

  5.times do
    puts "Child write #{longstr.size} chars"
    write_pipe.write(longstr)
    sleep 5
  end

  write_pipe.close
end

unless (pid.nil?)
  sleep 1

  write_pipe.close

  begin
    loop do
      # p read_pipe.eof?
      tmp = read_pipe.read_nonblock(10000000)
      puts "Parent read #{tmp.size} chars"
      sleep 1
    end
  rescue EOFError => e # 読み込み完了
    p e
  end

  read_pipe.close

  pid, status = Process.wait2(pid)
end


# start_loop
# queue_start_loop
