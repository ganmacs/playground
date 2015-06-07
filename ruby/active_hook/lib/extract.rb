require 'active_support/core_ext/array/extract_options'

ary = [1, 2, 3, a: :b]
p ary.extract_options!
p ary

module B
  def hook(*options)
    opts = options.extract_options!

    opts = {
      only: [:a, :b, :c]
    }.merge!(opts)

    types = Array(opts.delete(:only))

    p types
  end
end

class A
  extend B

  hook :a_hook, :b_hook, only: :after
end
