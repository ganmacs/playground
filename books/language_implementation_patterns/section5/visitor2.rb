class AST; end

class Add < AST
  attr_reader :left, :right

  def initialize(left, right)
    @left = left
    @right = right
  end
end

class Mul < AST
  attr_reader :left, :right

  def initialize(left, right)
    @left = left
    @right = right
  end
end

class IntNode < AST
  attr_reader :value

  def initialize(value)
    @value = value
  end
end

class Visitor
  def print_n(node)
    case node
    when Add
      print '(+ '
      print_n node.left
      print ' '
      print_n node.right
      print ')'
    when Mul
      print '(* '
      print_n node.left
      print ' '
      print_n node.right
      print ')'
    when IntNode
      print node.value
    end
  end
end


v = Visitor.new
plus = Add.new(IntNode.new(1), IntNode.new(2))
mul = Mul.new(IntNode.new(3), plus)
v.print_n(mul)
