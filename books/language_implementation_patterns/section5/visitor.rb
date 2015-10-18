class AST
  def visit(visitor)
    visitor.visit(self)
  end
end

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
  def visit(node)
    case node
    when Mul
      print '(* '
      node.left.visit(self)
      print ' '
      node.right.visit(self)
      print ')'
    when Add
      print '(+ '
      node.left.visit(self)
      print ' '
      node.right.visit(self)
      print ')'
    when IntNode
      print node.value
    end
  end
end

visitor = Visitor.new
plus = Add.new(IntNode.new(1), IntNode.new(2))
mul = Mul.new(IntNode.new(3), plus)
mul.visit(visitor)
