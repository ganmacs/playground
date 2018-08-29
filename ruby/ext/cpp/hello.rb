require_relative './test'

a = Test::Core::Server.new
p a.start(1)
