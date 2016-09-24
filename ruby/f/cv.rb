require 'thread'

cv = ConditionVariable.new

# class State
#   def initialize
#     @s = false
#     @mutex = Mutex.new
#   end

#   def run_once(name)
#     unless @s
#       p "start! #{name}"
#       @s = true
#       p "running! #{name}"
#       @s = false
#       p "finish! #{name}"
#     end
#   end
# end

class State
  def initialize
    @s = false
    @mutex = Mutex.new
  end

  def run_once(name)
    unless @mutex.synchronize { @s }
      @mutex.synchronize {
        p "start!   #{name}"
        @s = true
      }

      p "running! #{name}"

      @mutex.synchronize {
        @s = false
        p "finish!  #{name}"
      }
    end
  end
end

s = State.new
N = 100

v = N.times.map { |i|
  Thread.new(i) do |i|
    s.run_once(i)
  end
}

v.each(&:join)

puts nil, '<============================================================ OUTPUT START HERE'
sleep
