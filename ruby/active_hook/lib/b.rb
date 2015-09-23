module B
end

class A
  def self.method_missing(name, *args)
    p "#{name} in method_missing"
  end
end


A.include(B)
A.send(:include, B)
A.send(:missing_method, B)

# => "missing_method in method_missing"
