# frozen_string_literal: true

# botchi

class B
  def initialize(a)
    @a = a
  end

  def pp
    @a
  end
end

class A
  def pp(arg)
    B.new(arg)
  end
end


class C
  attr_reader :a

  def set(a)
    @a = a
  end
end

a = A.new
a = nil

c = C.new

p a&.pp(c.set(:a))&.pp
p c.a

# dig

d = { a:
        { b:
            { c: "d"
            }
        }
    }

e = [1, [2, [3, [4]]]]

p d.dig(:a, :b, :c)
p d.dig(:a, :d, :c)

p e.dig(1, 1, 1, 0)
# p e.dig(1, 0, 1, 0)


# fetch values



f = { a: { b:
             { c: "d"
             }
         },
      e: { b:
             { c: "d"
             }
         }
    }


p f.fetch_values(:a, :e)

# neg pos

kkk = (-2..2)

p kkk.select(&:negative?)
p kkk.select(&:positive?)


bbb = "asdfa"
begin
  bbb << "a"
rescue RuntimeError => e
  p e
end
