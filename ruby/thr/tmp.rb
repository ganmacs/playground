# require 'thread'

q = Queue.new

workers = 3.times.map do |i|
  Thread.start do
    n = "thread - #{i}"
    while (c = q.pop)
      c.call(n)
    end
  end
end

3.times.each do |i|
  5.times do |j|
    q.push -> (n) { sleep(1);  puts "#{n}: invoke job #{j} in maker thread- #{i}" }
  end
end

puts nil, '<============================================================ OUTPUT START HERE'
puts '<============================================================ OUTPUT CLOSE HERE', nil

# workers.each(&:join)

# workers.map(&:join)

# q.push -> (n) { puts "#{n}: invoke job " }

# sleep 1

# maker.map(&:join)
