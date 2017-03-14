require "logger"
require "cool.io"
require "eve/ticker"
require "eve/server"
require "eve/client"

module Eve
  class Agent
    DEFAULT_ADDR = "127.0.0.1"
    DEFAULT_PORT = 4321
    DEFAULT_LOOP = Cool.io::Loop.default
    DEFAULT_HEARTBEAT_RATE = 1      # 1 sec

    def initialize(options)
      @addr = options.fetch(:addr, DEFAULT_ADDR)
      @port = options.fetch(:port, DEFAULT_PORT)
      @loop = options.fetch(:evloop, DEFAULT_LOOP)
      @heartbeat_rate = options.fetch(:heartbeat_rate, DEFAULT_HEARTBEAT_RATE)
      @cluster = options.fetch(:cluster, []) # ['127.0.0.1:1234', ...]
      @logger = Logger.new(options.fetch(:log_output, STDOUT))
      @logger.level = ENV['LOG_LEVEL'] || Logger::INFO

      @server = Server.new(@addr, @port, @loop, @logger, options[:name])
      @clients = @cluster.map do |c|
        addr, port = c.split(":")
        Client.new(addr, port, @loop, @logger) # adder should be fixed
      end
    end

    def start
      @server.listen
      return unless leader?

      Ticker.start(@heartbeat_rate) do
        heartbeat
      end
    end

    private

    def leader?
      !@clients.empty?
    end

    def heartbeat
      @clients.each do |c|
        Thread.new(c) do |cc|
          cc.request("ping")
        end
      end
    end
  end
end
