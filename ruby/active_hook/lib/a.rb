module B
  def b
    'b'
  end
end

# 下はどっちもおなじ

class A
  include B
end

# -----

class A
end
A.include(B)

p A.new.b
