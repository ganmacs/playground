class Base
  def self.handle(name)
    names << name
  end

  def self.names
    @@names ||= []
  end
end
