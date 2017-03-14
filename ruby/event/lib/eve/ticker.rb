module Eve
  class Ticker
    def self.start(duraiton, &block)
      new.start(duraiton, block)
    end

    def start(duraiton, block)
      t = Thread.current
      @t = Thread.new do
        loop do
          begin
            block.call
            sleep duraiton
          rescue => e
            t.raise(e)            # ok?
            break
          end
        end
      end
    end

    def stop
      @t.kill
    end
  end
end
