class Parsed
  attr_reader :value, :derivs

  def initialize(value, derivs)
    @value = value
    @derivs = derivs
  end

  def value?(op)
    value == op
  end
end

class Derivs
  def initialize(str)
    @str = str
  end

  def dv_additive
    rule(:addtivie) do
      left = derivs.dv_mutiltive \
      and plus = left.derivs.dv_char \
      and plus.value?('+') \
      and right = plus.derivs.dv_mutiltive \
      and ::Parsed.new(left.value + right.value, right.derivs) \
      or derivs.dv_mutiltive
    end
  end

  def dv_mutiltive
    rule(:mutiltive) do
      left = derivs.dv_primary \
      and mul = left.derivs.dv_char \
      and mul.value?('*') \
      and right = mul.derivs.dv_mutiltive \
      and ::Parsed.new(left.value * right.value, right.derivs) \
      or derivs.dv_primary
    end
  end

  def dv_primary
    rule(:priamry) do
      lparn = derivs.dv_char \
      and lparn.value?('(') \
      and addtive = lparn.derivs.dv_additive \
      and rparn = addtive.derivs.dv_char \
      and rparn.value?(')') \
      and ::Parsed.new(addtive.value, rparn.derivs) \
      or derivs.dv_decimal
    end
  end

  def dv_decimal
    rule(:decimal) do
      if derivs.dv_char
        parsed = derivs.dv_char
        case parsed.value
        when '0' then ::Parsed.new(0, parsed.derivs)
        when '1' then ::Parsed.new(1, parsed.derivs)
        when '2' then ::Parsed.new(2, parsed.derivs)
        when '3' then ::Parsed.new(3, parsed.derivs)
        when '4' then ::Parsed.new(4, parsed.derivs)
        when '5' then ::Parsed.new(5, parsed.derivs)
        when '6' then ::Parsed.new(6, parsed.derivs)
        when '7' then ::Parsed.new(7, parsed.derivs)
        when '8' then ::Parsed.new(8, parsed.derivs)
        when '9' then ::Parsed.new(9, parsed.derivs)
        end
      end
    end
  end

  def dv_char
    rule(:char) do
      ::Parsed.new(@str[0...1], Derivs.new(@str[1..-1])) if @str.size > 0
    end
  end

  private

  def rule(key)
    if value.key?(key)
      value[key]
    else
      value[key] = yield
    end
  end

  def value
    @value ||= {}
  end

  def derivs
    @derivs ||= Derivs.new(@str)
  end
end

def evaluate(str)
  d = Derivs.new(str)
  if d.dv_additive
    d.dv_additive.value
  else
    raise 'No Parse'
  end
end

puts evaluate('1+2*(1+2)')
