require 'pp'

class Tree
  attr_accessor :right, :left, :value

  def initialize(value, left = nil, right = nil)
    @value = value
    @left = left
    @right = right
  end

  # @param [Fixnum] x
  def insert(x)
    if x < @value
      if @left
        @left.insert(x)
      else
        @left = Tree.new(x)
      end
    elsif x > @value
      if @right
        @right.insert(x)
      else
        @right = Tree.new(x)
      end
    end

    self
  end

  # @param [Fixnum] xs
  def insert_elems(xs)
    xs.each do |x|
      insert(x)
    end

    self
  end

  def has?(x)
    if @value == x
      true
    else
      if tree = select_tree(x)
        tree.has?(x)
      else
        false
      end
    end
  end

  def delete(x)
    if x == @value
      case
      when has_two_children?
        node = find_max(@left)
        @value = node.right.value
        node.right = nil
      when has_right_child?
        @value = @right.value
        l = @right.left
        r = @right.right
        @left = l
        @right = r
      when has_left_child?
        @value = @left.value
        l = @left.left
        r = @left.right
        @left = l
        @right = r
      else
        @value = nil
      end
    else
      node = select_tree(x)
      node.delete(x)
    end
  end

  def traverse(&block)
  end

  def to_s
    @left.to_s
    print "#{@value} " if @value
    @right.to_s
  end

  protected

  def find_max(tree)
    if tree.right
      tree.find_max(@right)
    else
      self
    end
  end

  private

  # return left or right tree
  def select_tree(x)
    if @value > x
      @left
    elsif @value < x
      @right
    end
  end

  def has_two_children?
    has_right_child? && has_left_child?
  end

  def has_right_child?
    !!@right
  end

  def has_left_child?
    !!@left
  end
end

puts a = Tree.new(10).insert_elems([13, 2, 4, 5, 1, 19, 14, 11, 12, 13])
puts a.delete(12)
# puts a.delete(10)
puts a
