require 'monitor'

buf = []
buf.extend(MonitorMixin)
cond_var = buf.new_cond

Thread.start do
  loop do
    buf.synchronize do
      cond_var.wait_while { buf.empty? }
      puts buf.shift
    end
  end
end

while line = ARGF.gets
  buf.synchronize do
    buf.push(line)
    cond_var.signal
  end
end
