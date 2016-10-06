require 'worker'

module Parallel
  class Core
    LIMIIT_OF_WORKER_SIZE = 10 # fix
    DEFAULT_WORKER_SIZE = 3 # fix

    def initialize(sources, options = {}, block)
      @sources = sources
      @options = options
      @block = block

      @worker_number = [LIMIIT_OF_WORKER_SIZE, @options.fetch(:worker_size, DEFAULT_WORKER_SIZE).to_i].min
      @workers = create_worker(@worker_number)
    end

    def run
    end

    def create_worker(n)
      workers = []
      Array.new(n).map do |i|
        workers << worker(@block)
      end
      workers
    end

    def worker(@block)



      Worker.new
    end
  end
end
