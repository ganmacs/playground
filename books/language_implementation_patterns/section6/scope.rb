Symbl = Struct.new(:name, :type)

class VariableSymbol < Symbl
  def initialize(*)
    super
  end
end

module Type
  def tname
    @name
  end
end

class BuildInTypeSymbol < Symbl
  include Type

  def initialize(name)
    super(name, nil)
  end
end

module Scope
  def scope_name
  end

  def enclosesing_scope
  end

  def define_sym
  end

  def resolve
  end
end
