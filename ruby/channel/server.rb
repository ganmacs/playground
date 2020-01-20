require 'fileutils'
require 'socket'
require 'tmpdir'
require 'logger'
require 'fcntl'

$logger = Logger.new(STDOUT)

def create_fifo_if_need(name)
  if !File.exist?(name)
    $logger.info("Created named pipe. path: #{name}")
    File.mkfifo(name)
  elsif File.ftype(name) != "fifo"
    raise "file exists but file type is FIFO. you should delete or change name: #{name}"
  else
    # already exists. does nothing
  end
end

class Writer
  def initialize(path)
    @path = path
  end

  def write(data)
    $logger.info("write data")
    @writer ||= File.open(@path, 'w')
    size = [data.bytesize].pack('N')
    @writer.write(size + data)
    @writer.flush
  end
end

class ReadBuf
  def self.open(path)
    new(path, logger: $logger)
  end

  def initialize(path, logger:)
    @reader = File.open(path, File::RDONLY | File::NONBLOCK)
    @buffer = +''.b
    @logger = logger
  end

  def read
    r, _ = IO.select([@reader], [], [])
    data = r.first.read_nonblock(1024, nil, exception: false)

    case data
    when :wait_readable
    # nothing
    when nil # nil means EOF
    else
      @buffer += data
    end

    if @buffer.empty?
      return nil
    end

    size = @buffer.slice!(0, 4).unpack('N').first
    @buffer.slice!(0, size)
  end
end

path = './server'

create_fifo_if_need(path)

$logger.info("read data")
reader = ReadBuf.open(path)
client_path = reader.read
$logger.info("received_message client_path: #{client_path}" )

w = Writer.new(client_path)
w.write("ok")
w.write('restart')
w.write("end")
