class Base; end

class A < Base; end

class B < Base; end

class C; end

[A, B, C].map(&:new).each do |e|
  case e
  when Base
    p "#{e.class} object in Base"
  else
    p "#{e.class} object in Else"
  end
end
