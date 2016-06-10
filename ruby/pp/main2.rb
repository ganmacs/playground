class Ary
  def initialize(*elems)
    @elems = elems
  end

  def format(q)
    q.println '['

    q.nest do
      @elems.each do |e|
        q.indent_printf("%s,\n", q.format(e))
      end
    end
    q.indent_printf ']'
  end
end

class Prim
  def initialize(v)
    @v = v
  end

  def format(q)
    q.print @v.inspect
  end
end

class Map
  def initialize(map)
    @map = map
  end

  def format(q)
    q.println '{'

    q.nest do
      @map.each do |k, v|
        q.indent_printf("%s: %s,\n", q.format(k), q.format(v))
      end
    end
    q.indent_printf '}'
  end
end

class Sym
  def initialize(v)
    @v = v
  end

  def format(q)
    q.print ":#{@v}"
  end
end

class PP
  def self.pp(obj)
    puts Printer.new(obj, 0).to_s
  end

  class Printer
    def initialize(obj, depth)
      @obj = obj
      @depth = depth
      @buffer = []
    end

    def to_s
      @obj.format(self)
      flush
    end

    def format(obj)
      q = self.class.new(obj, @depth)
      q.to_s
    end

    def print(txt)
      @buffer << txt
    end

    def indent_printf(f, *args)
      self.printf(indent + f, *args)
    end

    def printf(f, *args)
      self.print(sprintf(f, *args))
    end

    def println(txt)
      self.print(txt + "\n")
    end

    def nest
      @depth += 1
      begin
        yield
      ensure
        @depth -= 1
      end
    end

    private

    def flush
      @buffer.join
    end

    def indent
      '  ' * @depth
    end
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

c = Ary.new(
  Prim.new(1),
  b,
  Prim.new(3),
  Prim.new(5),
)

m = Map.new({
              Sym.new("k1") => Prim.new(1),
              Sym.new("k2") => Prim.new(2),
              Sym.new("ary") => c
            })

PP.pp(m)
