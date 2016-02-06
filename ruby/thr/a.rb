require 'thread'

q = Queue.new
ths = Array.new(3) do |x|
  Thread.start do
    while (d = q.deq)
      puts "#{d} in #{x}"
    end
  end
end

ths.each do |x|
  puts x
end

[:resource1, :resource2, :resource3, nil, nil, nil, nil].each do |r|
  q.enq r
end

ths.each do |x|
  puts x.inspect
end

ths.each(&:join)

# th1 = Thread.start do
#   while resource = q.deq
#     puts resource
#   end
# end

# [:resource1, :resource2, :resource3, nil].each do |r|
#   q.enq r
# end

# th1.join
