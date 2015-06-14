module A
  p 'in a start'
  def self.included(base)
    puts 'in a'
    puts base
  end
  p 'in a end'
end

module B
  p 'in b start'

  include A

  def self.included(base)
    puts 'in b'
    puts base
  end
  p 'in b end'
end

class C
  p 'in c start'
  include B
  p 'in c end'
end

C.new
# ------------

module A
  p 'in a start'
  def self.included(base)
    puts 'in a'
    puts base
  end
  p 'in a end'
end

module B
  p 'in b start'

  include A

  def self.extended(base)
    puts 'in b'
    puts base
  end
  p 'in b end'
end

class C
  p 'in c start'
  extend B
  p 'in c end'
end

C.new
