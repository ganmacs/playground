
class Store
  VALUE = Struct.new(:value, :at)

  def initialize
    @dict = {}
  end

  attr_reader :dict

  def inc(key)
    v = @dict[key]
    v.value += 1
    v.at = Time.now
  end

  def init(key)
    @dict[key] = VALUE.new(0, Time.now)
  end
end

s = Store.new
key = 'hoge'

s.init(key)
s.inc(key)
s.inc(key)

p s.dict
