require 'active_support'

data = {
  id: 3,
  name: {
    short: 'たま',
    logn: [
      'あ',
      'い'
    ]
  }
}

json = ActiveSupport::JSON.encode(data)
print json

# module JSONO
#   def self.encode
#     Encoding.json_encoder
#   end

#   module Encoding
#     class << self
#       attr_accessor :json_encoder
#     end

#     self.json_encoder = 'asf'
#   end
# end

# class A
#   attr_reader :a

#   def initialize(a)
#     @a = a
#   end
# end

# a = A.new('hoge')
# json = ActiveSupport::JSON.encode(a)
# p json

# p JSONO.encode
