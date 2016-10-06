module Parallel
  class Worker
    def initialize(options = {}, block)
      @options = options
      @block = block
    end

    def run
    end
  end
end
