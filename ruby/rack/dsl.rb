class A
  def initialize(name, &block)
    @name = name
    instance_eval(&block) if block_given?
  end

  def map(path, &block)
    set(:get, path, block)
  end

  def get(path)
    key = [:get, path]
    route_table[key].call
  end

  private

  def set(name, path, block)
    key = [name, path]
    route_table[key] = block
  end

  def route_table
    @route_table ||= {}
  end
end

app = A.new('this is A') do
  map "/" do
    [200, { "Content-Type" => "text/plain" }, ['root']]
  end
end

p app.get("/")
