class Object
  def current_method_name
    caller.first.match(/`(?<method_name>.*)'/)[:method_name]
  end

  def current_method
    caller.first.scan(/`(.*)'/).to_s
  end
end

puts current_method_name
puts current_method
