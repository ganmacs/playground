require 'leader/node'

module Leader
  class CLI
    def self.start
      new.start
    end

    def initialize
      @node = Node.new
    end

    def start
      @node.start
    end

    # def stop
    #   @node.stop
    # end
  end
end
