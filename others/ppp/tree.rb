class Tree
  attr_accessor :value, :right, :left

  def initialize(value, left = nil, right = nil)
    @value = value
    @left = left
    @right = right
  end

  # @param [Fixnum] x
  def insert!(x)
    node = insert(x)
    set(node)
  end

  def insert(x)
    if x < @value
      if has_left_child?
        Tree.new(@value, @left.insert(x), @right)
      else
        Tree.new(@value, Tree.new(x), @right)
      end
    elsif x > @value
      if has_right_child?
        Tree.new(@value, @left, @right.insert(x))
      else
        Tree.new(@value, @left, Tree.new(x))
      end
    else
      self
    end
  end

  # @param [[Fixnum]] xs
  def insert_elems!(xs)
    xs.each { |x| insert!(x) }
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

  def delete!(x)
    node = delete(x)
    set(node)
  end

  def delete(x)
    if x == @value
      case
      when has_two_children?
        Tree.new(@left.find_max, @left.delete_max, @right)
      when has_right_child? then @right
      when has_left_child? then @left
      end
    else
      if x > @value
        Tree.new(@value, @left, @right.delete(x))
      else
        Tree.new(@value, @left.delete(x), @right)
      end
    end
  end

  def to_s
    @left.to_s
    print "#{@value} "
    @right.to_s
  end

  protected

  def find_max
    if @right
      @right.find_max
    else
      @value
    end
  end

  def delete_max
    if @right
      Tree.new(@value, @left, @right.delete_max)
    else
      nil
    end
  end

  private

  def set(node)
    @value = node.value
    @left = node.left
    @right = node.right
    self
  end

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

puts a = Tree.new(10).insert_elems!([13, 2, 4, 5, 1, 19, 14, 11, 12, 13])
a.insert!(9)
a.delete!(10)
a.delete!(1)
a.delete!(2)
a.delete!(4)
a.delete!(19)
a.delete!(12)
a.insert!(100)
a.insert!(10)
puts a
