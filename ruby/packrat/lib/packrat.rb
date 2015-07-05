class Operation
  class << self
    def additive?(derivs)
      if derivs.dv_mutiltive
        left, derivs2 = derivs.dv_mutiltive

        if derivs2.dv_char
          op, derivs3 = derivs2.dv_char
          if op == '+'
            if derivs3.dv_mutiltive
              right, derivs4 = derivs3.dv_mutiltive
              [left + right, derivs4]
            else
              derivs.dv_mutiltive
            end
          else
            derivs.dv_mutiltive
          end
        else
          derivs.dv_mutiltive
        end
      else
        derivs.dv_mutiltive
      end
    end

    def multitive?(derivs)
      if derivs.dv_primary
        left, derivs2 = derivs.dv_primary

        if derivs2.dv_char
          op, derivs3 = derivs2.dv_char
          if op == '*'
            if derivs3.dv_mutiltive
              right, derivs4 = derivs3.dv_primary
              [left * right, derivs4]
            else
              derivs.dv_primary
            end
          else
            derivs.dv_primary
          end
        else
          derivs.dv_primary
        end
      else
        derivs.dv_primary
      end
    end

    def primary?(derivs)
      if derivs.dv_char
        op, derivs2 = derivs.dv_char
        if op == '('
          if derivs2.dv_additive
            v, derivs3 = derivs2.dv_additive
            op, derivs4 = derivs3.dv_char
            if op == ')'
              [v, derivs4]
            else
              derivs.dv_decimal
            end
          else
            derivs.dv_decimal
          end
        else
          derivs.dv_decimal
        end
      else
        derivs.dv_decimal
      end
    end

    def decimal?(derivs)
      if derivs.dv_char
        n, derivs2 = derivs.dv_char
        case n
        when '0' then [0, derivs2]
        when '1' then [1, derivs2]
        when '2' then [2, derivs2]
        when '3' then [3, derivs2]
        when '4' then [4, derivs2]
        when '5' then [5, derivs2]
        when '6' then [6, derivs2]
        when '7' then [7, derivs2]
        when '8' then [8, derivs2]
        when '9' then [9, derivs2]
        end
      end
    end
  end
end

class Derivs
  def initialize(str)
    @str = str
  end

  def dv_additive
    rule(:addtivie) do
      Operation.additive?(derivs)
    end
  end

  def dv_mutiltive
    rule(:mutiltive) do
      Operation.multitive?(derivs)
    end
  end

  def dv_primary
    rule(:priamry) do
      Operation.primary?(derivs)
    end
  end

  def dv_decimal
    rule(:decimal) do
      Operation.decimal?(derivs)
    end
  end

  def dv_char
    rule(:char) do
      [@str[0...1], Derivs.new(@str[1..-1])] if @str.size > 0
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
    d.dv_additive[0]
  else
    raise 'No Parse'
  end
end

puts evaluate('1+2*(1+2)')
