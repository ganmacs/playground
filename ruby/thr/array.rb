class List
  def initialize(v = [])
    @array = v
  end

  def to_s
    @array
  end

  def push(v)
    @array << v
  end

  def pop
    @array.pop
  end

  def register(vs)
    @array += Array(vs)
  end

  def empty?
    @array.empty?
  end

  def map(&block)
    @array.map(block)
  end

  def select(&block)
    @array.select(&block)
  end

  def delete(&block)
    @array.delete(block)
  end
end


ary = List.new([10, 20, 30])

a = Thread.start do
  ary.push(1)
  ary.push(2)
  ary.push(3)
  ary.push(5)
end


b = Thread.start do
  p ary.empty?
  p ary
end

c = Thread.start do
  ary.delete(&:odd?)
  p ary
end

sleep 1

d = Thread.start do
  v = ary.select(&:odd?)
  ary.register(v.map { |e| e + 1 })
end

[a, b, c, d].each(&:join)

p ary
