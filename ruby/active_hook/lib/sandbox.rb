module B
  def b
    'b'
  end
end

class A
end

A.send(:include, B)
A.include(B)

p A.new.b                       # => b
