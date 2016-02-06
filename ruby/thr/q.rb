require 'thread'

q = Queue.new

th1 = Thread.start do
  while resource = q.pop
    puts resource
  end
end

[:resource1, :resource2, :resource3, nil].each{ |r|
  q.push(r)
}

puts nil, '<============================================================ OUTPUT START HERE'
puts '<============================================================ OUTPUT CLOSE HERE', nil

th1.join
