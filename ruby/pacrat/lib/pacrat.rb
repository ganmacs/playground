class Operation
  class << self
    def additive?(derivs)
      alt2 = -> { derivs.dv_mutiltive if derivs.dv_mutiltive }

      if derivs.dv_mutiltive
        left, derivs2 = derivs.dv_mutiltive

        if derivs2.dv_char
          op, derivs3 = derivs2.dv_char
          if op == '+'
            if derivs3.dv_mutiltive
              right, derivs4 = derivs3.dv_mutiltive
              [left + right, derivs4]
            else
              alt2.call
            end
          else
            alt2.call
          end
        else
          alt2.call
        end
      else
        alt2.call
      end
    end

    def multitive?(derivs)
      alt2 = -> { derivs.dv_primary if derivs.dv_primary }
      if derivs.dv_primary
        left, derivs2 = derivs.dv_primary

        if derivs2.dv_char
          op, derivs3 = derivs2.dv_char
          if op == '*'
            if derivs3.dv_mutiltive
              right, derivs4 = derivs3.dv_primary
              [left * right, derivs4]
            else
              alt2.call
            end
          else
            alt2.call
          end
        else
          alt2.call
        end
      else
        alt2.call
      end
    end

    def primary?(derivs)
      alt2 = -> { derivs.dv_decimal if derivs.dv_decimal }
      if derivs.dv_char
        op, derivs2 = derivs.dv_char
        if op == '('
          if derivs2.dv_additive
            v, derivs3 = derivs2.dv_additive
            op, derivs4 = derivs3.dv_char
            if op == ')'
              [v, derivs4]
            else
              alt2.call
            end
          else
            alt2.call
          end
        else
          alt2.call
        end
      else
        alt2.call
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
    @additive ||= Operation.additive?(derivs)
  end

  def dv_mutiltive
    @multitive ||= Operation.multitive?(derivs)
  end

  def dv_primary
    @primary ||= Operation.primary?(derivs)
  end

  def dv_decimal
    @decimal ||= Operation.decimal?(derivs)
  end

  def dv_char
    @char ||= begin
                [@str[0...1], Derivs.new(@str[1..-1])] if @str.size > 1
              end
  end

  private

  def derivs
    @derivs ||= Derivs.new(@str)
  end
end

def evaluate(str)
  d = Derivs.new(str)
  if d.dv_additive
    puts d.dv_additive
  else
    raise 'No Parse'
  end
end

evaluate('1+2*3')
