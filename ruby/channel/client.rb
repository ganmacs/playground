require 'fileutils'
require 'socket'
require 'tmpdir'
require 'logger'
require 'fcntl'

$logger = Logger.new(STDOUT)

def create_fifo_if_need(name)
  if !File.exist?(name)
    $logger.info("Created named pipe. path: #{name}")
    File.mkfifo(name, 0777)
  elsif File.ftype(name) != "fifo"
    raise "file exists but file type is FIFO. you should delete or change name: #{name}"
  else
    # already exists. does nothing
  end
end

class Reader
  def self.open(path)
    new(path, logger: $logger)
  end

  def initialize(path, logger:)
    @reader = File.open(path, File::RDONLY | File::NONBLOCK)
    @buffer = +''.b
    @logger = logger
  end

  def read
    ret = parse(@buffer)
    return ret if ret

    r, _ = IO.select([@reader], [], [])
    data = r.first.read_nonblock(1024, nil, exception: false)

    case data
    when nil
    # nil means EOF
    when :wait_readable
    # nothing
    else
      @buffer += data
    end

    if @buffer.empty?
      return nil
    end

    parse(@buffer)
  end

  private

  def parse(data)
    if data.bytesize < 4
      return nil
    end

    sizebuf = data.slice(0, 4)
    unless sizebuf.size == 4
      return nil
    end

    size = sizebuf.unpack('N').first

    ret = data.slice(4, size)
    if ret.bytesize == size
      data.slice!(0, size + 4)
    else
      nil
    end
  end
end

class Writer
  def initialize(path)
    @path = path
  end

  def write(data)
    $logger.info("write data")
    size = [data.bytesize].pack('N')

    writer.write(size + data)
    writer.flush
  end

  private

  def writer
    @writer ||= File.open(@path, 'w')
  end
end

path = './client'
server_path = './server'
create_fifo_if_need(path)

$logger.info("read data")
reader = Reader.open(path)

$logger.info("write data")
writer = Writer.new(server_path)
writer.write(path)

while (r = reader.read)
  $logger.info("recv:#{r}")

  case r
  when 'end'
    break
  when 'restart'
  # write(writer, path)
  else
    p "nothing #{r}"
  end
end
