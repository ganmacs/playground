require_relative './sample1.rb'
require_relative './sample2.rb'

def run(class_name)
  klass = Handler.const_get(class_name)
  klass.new.call
end

['PlugA', 'PlugB'].each do |e|
  run e
end
