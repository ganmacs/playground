$LOAD_PATH << File.expand_path('.')

require 'bidi_channel'
require 'logger'

$logger = Logger.new(STDOUT)

server = BidiChannel::Server.new(logger: $logger)

env = {
  BidiChannel::FifoChannel::CHANNEL_PATH_ENV_NAME => BidiChannel::FifoChannel.server_name
}

t = Thread.new do
  server.setup_connection
  server.recv do |msg, _writer|
    p msg
    server.finish
  end
end

pid = Process.spawn(env, 'ruby ./app_client.rb')

Process.waitpid(pid)

t.join



# # require 'fileutils'
# # require 'socket'
# # require 'tmpdir'
# # require 'logger'
# # require 'fcntl'


# # module COMMAND
# #   JOIN = '0'
# #   LEAVE = '1'
# #   OP = '2'
# #   SUCCESS = '3'
# #   FAIL = '4'
# # end

# # class Channel
# #   def self.channel_dir
# #     # @channel_dir ||= Dir.mktmpdir('fleunt_channel')
# #     Dir.pwd
# #   end
# # end


# # class Client
# #   def initialize(name:, server_name:)
# #     # server path should know
# #     @server = File.join(Channel.channel_dir, @server_name)
# #     @path = File.join(Channel.channel_dir, @name)

# #     # @reader_path = "#{@path}_reader"
# #     # @writer_path = "#{@path}_writer"
# #     # @writer = nil
# #   end

# #   def start
# #     create_fifo_if_need(@reader_path)
# #     @reader = File.open(@reader_path, File::RDONLY | File::NONBLOCK)
# #     @writer = File.open(@reader_, File::RDONLY | File::NONBLOCK)

# #     Thread.new do

# #     end
# #   end

# #   def create_fifo_if_need(name)
# #     if !File.exist?(name)
# #       @logger.info("Created named pipe. path: #{name}")
# #       File.mkfifo(name, 0777)
# #     elsif File.ftype(name) != "fifo"
# #       raise "file exists but file type is FIFO. you should delete or change name: #{name}"
# #     else
# #       # already exists. does nothing
# #     end
# #   end

# #   def actual_write(f, data)
# #     size = [data.bytesize].pack('N')
# #     f.write(size + data)
# #   end

# #   def parse(data)
# #     @buffer += data
# #     @buffer.slice(0, 4).unpack('N').first
# #     @buffer.slice!(4, size)
# #   end
# # end

# # # class ChannelProtocol

# # # end

# # class Server
# #   def initialize(name:)
# #     @name = name
# #     @path = File.join(Channel.channel_dir, @name)
# #     @reader_path = "#{@path}_sever_reader"
# #     # @writer_path = "#{@path}_writer"
# #     @writer = nil
# #     @buffer = ''.b
# #     @logger = Logger.new(STDOUT)
# #     @r, @w = IO.pipe
# #   end

# #   def start
# #     create_fifo_if_need(@reader_path)
# #     @reader = File.open(@reader_path, File::RDONLY | File::NONBLOCK)

# #     Thread.new do
# #       loop do
# #         data = @reader.read
# #         cmd, msg = data.split(' ', 2)

# #         case cmd
# #         when COMMAND::JOIN
# #           f = File.open(@reader_path, File::WRONLY)
# #           @logger.info("connected to #{msg}")
# #           data = "#{COMMAND::SUCCESS} ok"
# #           actual_write(f, data)
# #           @client << f
# #         when COMMAND::LEAVE
# #         when COMMAND::OP
# #         else
# #           raise "invalid #{buf}"
# #         end
# #       end
# #     end
# #   end

# #   def connect
# #     buf = parse(@reader.read)
# #   end

# #   def write(d)
# #     if @writer
# #       @writer.puts(d)
# #     else
# #       raise 'not now'
# #     end
# #   end

# #   def read
# #     p @reader.read
# #   end

# #   private

# #   def create_fifo_if_need(name)
# #     if !File.exist?(name)
# #       @logger.info("Created named pipe. path: #{name}")
# #       File.mkfifo(name, 0777)
# #     elsif File.ftype(name) != "fifo"
# #       raise "file exists but file type is FIFO. you should delete or change name: #{name}"
# #     else
# #       # already exists. does nothing
# #     end
# #   end

# #   def actual_write(f, data)
# #     size = [data.bytesize].pack('N')
# #     f.write(size + data)
# #   end

# #   def parse(data)
# #     @buffer += data
# #     @buffer.slice(0, 4).unpack('N').first
# #     @buffer.slice!(4, size)
# #   end
# # end



# #   # @params name [String]
# #   def initialize(name:)
# #     @logger = Logger.new(STDOUT)
# #     @name = name
# #     @buffer = +''.b
# #     @path = File.join(Channel.channel_dir, @name)
# #     @reader_path = "#{@path}_reader"
# #     @writer_path = "#{@path}_writer"
# #   end

# #   def create_channel
# #     create_fifo_if_need(@reader_path)
# #     create_fifo_if_need(@writer_path)

# #     # @reader = File.open(@reader_path, File::RDONLY | File::NONBLOCK)
# #     puts 'reader'
# #     @reader = File.open(@reader_path)
# #     puts 'reader2'

# #     @writer = File.open(@writer_path, File::WRONLY | File::NONBLOCK)
# #   end

# #   def stop
# #     @logger.info("stop")

# #     path = File.join(Channel.channel_dir, @name)
# #     FileUtils.rm_rf(path)
# #     # remove_entry_secure
# #   end

# #   def send(data)
# #     @logger.info("send data")
# #     size = [data.bytesize].pack('N')
# #     @file.write(size + data)
# #   end

# #   def read
# #     @logger.info "read"

# #     p @reader.read

# #     # p @buffer += @reader.read
# #     # p size = @buffer.slice(0, 4).unpack('N').first
# #     # @buffer.slice!(4, size)
# #   end

# #   private

# #   def create_fifo_if_need(name)
# #     if !File.exist?(name)
# #       @logger.info("Created named pipe. path: #{name}")
# #       File.mkfifo(name, 0777)
# #     elsif File.ftype(name) != "fifo"
# #       raise "file exists but file type is FIFO. you should delete or change name: #{name}"
# #     else
# #       # already exists. does nothing
# #     end
# #   end
# # end

# # c = Channel.new(name: 'fluent')
# # c.create_channel


# # p c.read


# # fork do
# #   c = Channel.new(name: 'fluent')
# #   # c.create_channel

# #   c.reopen
# #   c.send("hi")
# #   # p "server: #{c.read}"
# # end

# # c.create_channel
# # p c.read

# # File.open('fluent', 'r'){|f|
# #   puts f.read
# # }

# # p c.send("received")






# # p File.mkfifo('mypipe')

# # child_socket, parent_socket = Socket.pair(:UNIX, :DGRAM, 0)
# # p child_socket
# # maxlen = 1000

# # fork do
# #   parent_socket.close

# #   10.times do
# #     instruction = child_socket.recv(maxlen)
# #     child_socket.send("#{instruction} accomplished!", 0)
# #   end
# # end
# # child_socket.close

# # 5.times do
# #   parent_socket.send("Heavy lifting", 0)
# # end

# # 5.times do
# #   parent_socket.send("Feather lifting", 0)
# # end

# # 10.times do
# #   puts parent_socket.recv(maxlen)
# # end
