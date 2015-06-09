# require 'active_model/model'
require 'active_model/callbacks'
require 'active_support/callbacks'
require 'pp'

class Person
  extend ActiveModel::Callbacks
  define_model_callbacks :create

  before_create :hoge

  def create
    run_callbacks :create do
      p '---create---'
      # Your create action methods here
    end
  end

  def hoge
    p '---before---'
  end
end

# pp Person._create_callbacks?
Person.new.create

# Person.new.create

# class A
# end

# a = A.new
# p const_get(:A).new
# p a.singleton_class

# module A
#   def self.included(base)
#     p base
#   end

#   def hoge
#     p 'hoge'
#   end
# end

# class B
#   include A
# end

# # B.include(A).new.hoge
# B.new.hoge

# # class C
# # end

# C.define_singleton_method(:echo) { |*args| p args.join(',') }
# C.echo('asdf', 'a', 'b')
