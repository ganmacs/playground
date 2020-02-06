require 'fluent/config'
require 'fluent/config/element'

SectionStringBuilder = Struct.new(:name, :body, :indent_size, :arg) do
  def to_s
    indent = ' ' * indent_size

    if arg && !arg.empty?
      "#{indent}<#{name} #{arg}>\n#{body}\n#{indent}</#{name}>"
    else
      "#{indent}<#{name}>\n#{body}\n#{indent}</#{name}>"
    end
  end

  def to_element
    elem = body.to_element
    elem.name = name
    elem.arg = arg if arg
    elem.v1_config = true
    elem
  end
end

class RootBuilder
  def initialize(system, conf)
    @system = system
    @conf = conf
  end

  def to_element
    Fluent::Config::Element.new('ROOT', '', {}, [@system, @conf].map(&:to_element).flatten)
  end
end

class SectionBodyBuilder
  def initialize(indent, root: false)
    @indent = indent
    @bodies = []
    @root = root
  end

  def add_line(k, v)
    i = ' ' * @indent
    @bodies << [i, k, v]
  end

  def add_section(section)
    @bodies << section
  end

  def to_element
    if @root
      return @bodies.map(&:to_element)
    end

    not_section, section = @bodies.partition {|e| e.is_a?(Array) }

    r = {}
    not_section.each do |e|
      r[e[1]] = e[2]
    end

    if @root
      section.map(&:to_element)
    else
      Fluent::Config::Element.new('', '', r, section.map(&:to_element))
    end
  end

  def to_s
    b = @bodies.map do |v|
      v.is_a?(Array) ? "#{v[0]}#{v[1]} #{v[2]}" : v.to_s
    end

    if @root
      b.join("\n\n")
    else
      bjoin("\n")
    end
  end
end
