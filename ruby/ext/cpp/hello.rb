require_relative './test'

a = Test::Core::Server.new
p a.start(1)

3.times do
  fork do
    v = Test::Core::Hello.new(10)
    v.say()
  end
end

sleep 1

GC.start
