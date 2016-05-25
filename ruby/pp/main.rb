class Ary
  def initialize(*elems)
    @elems = elems
  end

  def pretty_print(q)
    q.println '['

    q.nest do
      q.interleave(@elems, ',') do |v|
        q.pp v
      end
    end

    q.println ']'
  end
end

class Prim
  def initialize(v)
    @v = v
  end

  def pretty_print(q)
    q.print @v.inspect
  end
end

class PP
  def self.pp(obj)
    q = new
    q.pp obj
    q.flush
  end

  def initialize(depth = 0, output = STDOUT, indent = '  ')
    @buffer = []
    @output = output
    @depth = depth
    @indent = indent
  end

  def interleave(ary, delim)
    ary.each do |e|
      yield e
      print delim
    end
  end

  def pp(obj)
    obj.pretty_print self
  end

  def flush
    @buffer.each do |line|
      @output << line
    end
  end

  def print(txt)
    @output << indented(txt)
  end

  def println(txt)
    self.print(txt + "\n")
  end

  def nest
    @depth += 1
    begin
      yield
    ensure
      @indent -= 1
    end
  end

  def indented(txt)
    indent + txt
  end

  private

  def indent
    @indent * @depth
  end
end

a = Ary.new(
  Prim.new(1),
  Prim.new(3),
  Prim.new(5),
)

b = Ary.new(
  Prim.new(1),
  Prim.new(3),
  Prim.new(5),
  a
)

PP.pp(b)
