class A
  def initialize
    @a = 0
    @b = nil
  end

  def mthd
    defined?(@a) && 'a'
  end

  def mthd2
    @a || 'b'
  end

  def mthd3
    (defined?(@a) && @a) || 1
  end

  def mthd4
    defined?(@b) && @b || 2
  end
end

a = A.new

p a.mthd
p a.mthd2
p a.mthd3
p a.mthd4
