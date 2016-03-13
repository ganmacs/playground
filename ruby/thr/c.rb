SIZE = 10

def countup
  counter = 0
  open('count.txt', 'r') { |f| counter = f.read.to_i + 1 }
  open('count.txt', 'w') { |f| f.write counter }
end

open('count.txt', 'w') do |f|
  f.write 0
end

m = Mutex.new
Array.new(SIZE).map {
  Thread.start {
    m.synchronize {
      countup
    }
  }
}.each(&:join)
