class A
  attr_reader :a, :b, :c

  def initialize(a, b, c)
    @a = a
    @b = b
    @c = c
  end

  def to_s
    [@a, @b, @c].to_s
  end
end

class Worker
  def initialize
    @read_pipe, @write_pipe = IO.pipe
  end

  def run
    @pid = fork do
      @read_pipe.close

      a = A.new(1, 2, 3)
      write_obj(a)

      @write_pipe.close
    end

    puts read_obj
    @read_pipe.close
  end

  def write_obj(obj)
    data = Marshal.dump(obj)
    @write_pipe.puts data
  end

  def read_obj
    data = @read_pipe.gets.chomp
    Marshal.load(data)
  end
end

Worker.new.run
