require 'time'

module BidiChannel
  class FifoChannel
    CHANNEL_PATH_ENV_NAME = 'BIDI_CHANNEL_PATH'.freeze
    CHANNEL_VAL = "__bidi_channel_server_fifo_path__".freeze

    def self.generate_name(name)
      # "BIDI_CHANNEL_#{name}_#{Time.now.utc.iso8601(6)}"
      "BIDI_CHANNEL_#{name}"
    end

    def self.server_name
      @server_name ||= generate_name('server_file')
    end

    def self.build_server
      c = new_with_base_dir(server_name)
      c.build
      c
    end

    def self.new_with_base_dir(name)
      base_dir = ENV['BIDI_CHANNEL_BASE_DIR'] || '/tmp'
      new(File.join(base_dir, name))
    end

    def self.build_from_env_var(name = nil)
      s = new_with_base_dir(ENV[name || CHANNEL_PATH_ENV_NAME])
      s.build
      s
    end

    # if the path is given, name will be ignored.
    def initialize(name)
      @name = name
    end

    attr_reader :name

    def build
      create_fifo_if_need(@name)
    end

    def channel_for_reader
      @channel_for_reader ||= File.open(@name, File::RDONLY | File::NONBLOCK)
    end

    def channel_for_writer
      @channel_for_writer ||= File.open(@name, 'w')
    end

    def close
      if instance_variable_defined?(:@channel_for_writer) || instance_variable_defined?(:@channel_for_reader)
        begin
          File.delete(@name)
        rescue
          # ignore for now
        end
      end
    end

    private

    def create_fifo_if_need(name)

      if !File.exist?(name)
        # $logger.info("Created named pipe. path: #{name}")
        File.mkfifo(name)
      elsif File.ftype(name) != "fifo"
        raise "file exists but file type is FIFO. you should delete or change name: #{name}"
      else
        # already exists. does nothing
      end
    end
  end
end
