class Worker
  def initialize(&block)
    @parent_read, @parent_write = IO.pipe
    @child_read, @child_write = IO.pipe
    @block = block
  end

  def run
    @pid = fork do
      close_parent_pipe
      puts 'asdf'
      write_to_parent(:ready)
      puts "asdfk"

      @block.call
    end

    if @pid
      wait_forked_notification_from_child
    else
      close_child_pipe
    end
  end

  private

  def wait_forked_notification_from_child
    close_child_pipe

    result = read_from_child
    raise "Failed to start worker pid #{@pid}" unless result == :ready
    result
  end

  def close_child_pipe
    @child_write.close
    @child_read.close
  end

  def close_parent_pipe
    @parent_read.close
    @parent_write.close
  end

  def read_object_from(pipe)
    data = pipe.gets
    Marshal.load(data.chomp.gsub('\n', "\n"))
  end

  def read_from_parent
    read_object_from(@child_read)
  end

  def read_from_child
    p @child_write
    read_object_from(@parent_read)
  end

  def write_object_to(obj, pipe)
    data = Marshal.dump(obj).gsub("\n", '\n') + "\n"
    pipe.write data
  end

  def write_to_parent(obj)
    p @child_write
    write_object_to(obj, @child_write)
  end

  def write_to_child
    write_object_to(obj, @parent_write)
  end
end

Worker.new do |*x|
  puts x
end.run
