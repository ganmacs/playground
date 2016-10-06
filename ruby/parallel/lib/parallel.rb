require 'parallel/core'

module Parallel
  class << self
    def map(sources, options = {}, &block)
      c = Core.new(sources, options, block)
      c.run
    end
  end
end
