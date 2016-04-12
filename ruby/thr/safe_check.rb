def a
  a = (1..10000).to_a
  k = []

  xa = []
  ya = []
  za = []
  va = []


  x = Thread.start do
    while !a.empty? && (r = a.pop)
      k.push r
      xa.push r
      p "call in x #{r}"
    end
  end

  y = Thread.start do
    while !a.empty? && (r = a.pop)
      k.push r
      ya.push r
      p "call in y #{r}"
    end
  end

  z = Thread.start do
    while !a.empty? && (r = a.pop)
      k.push r
      za.push r
      p "call in z #{r}"
    end
  end

  v = Thread.start do
    while !a.empty? && (r = a.pop)
      k.push r
      va.push r
      p "call in v #{r}"
    end
  end

  [x, y, z, v].each(&:join)

  p xa.size
  p ya.size
  p za.size
  p va.size
  p k.size
end

def b
  size = 10

  def countup(name)
    counter = 0
    open("#{name}.txt", 'r') { |f| counter = f.read.to_i + 1 }
    open("#{name}.txt", 'w') { |f| f.write counter }
  end

  open('count1.txt', 'w') do |f|
    f.write 0
  end

  open('count2.txt', 'w') do |f|
    f.write 0
  end

  Array.new(size).map {
    Thread.start do
      countup('count2')
    end
  }.each(&:join)

  m = Mutex.new
  Array.new(size).map {
    Thread.start {
      m.synchronize {
        countup('count1')
      }
    }
  }.each(&:join)
end

b
