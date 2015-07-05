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

  # dv_additive <- dv_mutiltive dv_additive_suffix
  def dv_additive
    rule(:addtivie) do
      left = derivs.dv_multitive \
      and vsuff = left.derivs.dv_additive_suffix \
      and ::Parsed.new(vsuff.value.call(left.value), vsuff.derivs) \
    end
  end

  # dv_additive_suffix <- + dv_multitive dv_additive_suffix
  #                    <- - dv_multitive dv_additive_suffix
  #                    <- empty
  def dv_additive_suffix
    rule(:addtivie_suffix) do
      (plus = derivs.dv_symbol \
       and plus.value?('+') \
       and vright = plus.derivs.dv_multitive \
       and vsuff = vright.derivs.dv_additive_suffix \
       and ::Parsed.new(-> x { vsuff.value.call(x + vright.value) }, vsuff.derivs)) \
      or \
      (minus = derivs.dv_symbol \
       and minus.value?('-') \
       and vright = minus.derivs.dv_multitive \
       and vsuff = vright.derivs.dv_additive_suffix \
       and ::Parsed.new(-> x { vsuff.value.call(x - vright.value) }, vsuff.derivs)) \
      or \
      ::Parsed.new(-> x { x }, derivs)
    end
  end

  # dv_multitive <- dv_primary dv_multitive_suffix
  def dv_multitive
    rule(:multitive) do
      left = derivs.dv_primary \
      and vsuff = left.derivs.dv_multitive_suffix \
      and ::Parsed.new(vsuff.value.call(left.value), vsuff.derivs) \
    end
  end

  # dv_multitive_suffix <- * dv_primary dv_multitive_suffix
  #                     <- / dv_primary dv_multitive_suffix
  #                     <- empty
  def dv_multitive_suffix
    rule(:mutiltive_suffix) do
      (mul = derivs.dv_symbol \
       and mul.value?('*') \
       and vright = mul.derivs.dv_primary \
       and vsuff = vright.derivs.dv_multitive_suffix \
       and ::Parsed.new(-> x { vsuff.value.call(x * vright.value) }, vsuff.derivs)) \
      or \
      (div = derivs.dv_symbol \
       and div.value?('/') \
       and vright = div.derivs.dv_primary \
       and vsuff = vright.derivs.dv_multitive_suffix \
       and ::Parsed.new(-> x { vsuff.value.call(x / vright.value) }, vsuff.derivs)) \
      or \
      ::Parsed.new(-> x { x }, derivs)
    end
  end

  def dv_primary
    rule(:priamry) do
      lparn = derivs.dv_symbol \
      and lparn.value?('(') \
      and addtive = lparn.derivs.dv_additive \
      and rparn = addtive.derivs.dv_symbol \
      and rparn.value?(')') \
      and ::Parsed.new(addtive.value, rparn.derivs) \
      or derivs.dv_decimal
    end
  end

  def dv_decimal
    rule(:decimal) do
      d = derivs.dv_digits \
      and dd = d.derivs.dv_whitespace \
      and ::Parsed.new(d.value[0], dd.derivs)
    end
  end

  def dv_digits
    rule(:digits) do
      if d = derivs.dv_digit
        if dd = d.derivs.dv_digits
          n = 10**dd.value[1]
          ::Parsed.new([(d.value * n) + dd.value[0], dd.value[1] + 1],  dd.derivs)
        else
          ::Parsed.new([d.value, 1], d.derivs)
        end
      end
    end
  end

  def dv_digit
    rule(:digit) do
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

  def dv_symbol
    rule(:symbol) do
      d = derivs.dv_char \
      and %w!+ = * / % ( )!.include?(d.value) \
      and dd = d.derivs.dv_whitespace \
      and ::Parsed.new(d.value, dd.derivs)
    end
  end

  def dv_whitespace
    rule(:whitespace) do
      if d = derivs.dv_char
        if d.value?(' ')
          d.derivs.dv_whitespace
        else
          ::Parsed.new(nil, derivs)
        end
      else
        ::Parsed.new(nil, derivs)
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

puts evaluate('(12 + 34) * 10000')
