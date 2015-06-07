class Class
  def define_hoge
    singleton_class.class_eval do
      define_method(:hoge) do
        puts "hoge in #{self}"
      end
    end
  end
end

class A

  define_hoge

  def self
    self.class
  end
end

p Object.const_get(:A).new
p A.new.self.new
A.hoge
