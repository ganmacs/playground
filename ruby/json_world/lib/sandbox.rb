def named_args(name: nil, **options)
  p name
  p options
end

named_args(
  name: 'hoge',
  id: 1,
  age: 20
)

module A
  def fuga
    p 'this is a public method'
  end

  private

  def hoge
    p 'this is a private method'
  end
end

class B
  extend A
  hoge
end
