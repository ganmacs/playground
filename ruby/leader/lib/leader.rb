require 'leader/cli'
require 'logger'

module Leader
  def self.logger
    @logger ||= begin
      l = Logger.new(STDOUT)
      l.level = ENV['LOG_LEVEL'] || :info
    end
  end
end
