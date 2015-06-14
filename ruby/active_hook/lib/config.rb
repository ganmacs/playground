require 'active_support/configurable'
require 'minitest/unit'
extend MiniTest::Assertions

class Configuration
  include ActiveSupport::Configurable

  config_accessor :max_page do
    10
  end
end

p Configuration.max_page
p Configuration.max_page = 100
p Configuration.max_page
assert(true)

c =  Configuration.new
p c.max_page
p c.max_page = 1
p Configuration.max_page
