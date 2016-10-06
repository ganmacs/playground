str = '+ 2 * + 1 5 + 2 3'

def polish_notation(input, stack = [])
  if input == []
    return stack.first
  else
    a = input.shift

    if '+-/*'.include?(a)
      stack.unshift(a.to_sym)
    else
      stack.unshift(a.to_i)
      while stack[0].class == Fixnum && stack[1].class == Fixnum
        r = stack.shift
        l = stack.shift
        op = stack.shift
        stack.unshift(l.send(op, r))
      end
    end

    polish_notation(input, stack)
  end
end

def parse(tokens)
  a = tokens.shift

  if '+-/*'.include?(a)
    l = parse(tokens)
    r = parse(tokens)
    l.send(a, r)
  else
    a.to_i
  end
end

p polish_notation(str.split(' '))
# p parse(str.split(' '))
