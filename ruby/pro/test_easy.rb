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
  def initialize(&block)
    @child_read, @parent_write = IO.pipe
    @parent_read, @child_write = IO.pipe
    @block = block
  end

  def run
    @pid = fork do
      close_child_pipe

      r = read_from_parent
      r2 = @block.call(r)
      write_to_parent(r2)

      close_parent_pipe
    end

    write_to_child(A.new(1, 2, 3))
    r = read_from_child
    puts r
  end

  def close_child_pipe
    @child_read.close
    @child_write.close
  end

  def close_parent_pipe
    @parent_write.close
    @parent_read.close
  end

  def write_obj(obj, pipe)
    data = Marshal.dump(obj)
    pipe.puts data
  end

  def write_to_parent(obj)
    write_obj(obj, @parent_write)
  end

  def write_to_child(obj)
    write_obj(obj, @child_write)
  end

  def read_obj(pipe)
    data = pipe.gets.chomp
    Marshal.load(data)
  end

  def read_from_parent
    read_obj(@parent_read)
  end

  def read_from_child
    read_obj(@child_read)
  end
end

Worker.new do |x|
  puts "child process"
  sleep(2)                 # blocking
  A.new(1, 2, x)
end.run
