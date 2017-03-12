require 'leader/cli'
require 'logger'

module Leader
  def self.logger
    @logger ||= Logger.new(STDOUT).tap do |l|
      l.level = ENV['LOG_LEVEL'] || :info
    end
  end
end
