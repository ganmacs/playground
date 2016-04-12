class A
  attr_reader :sum

  def initialize
    @sum = []
    @mutex = Mutex.new
  end

  def countup
    @mutex.synchronize {

      10.times.each do |e|
        if @sum.include?(e)
          p e
        else
          sleep 0.1
          @sum << e
        end
      end
    }
  end
end

a = A.new
Array.new(5).map {
  Thread.start { a.countup }
}.each(&:join)

p a.sum
p a.sum.size
