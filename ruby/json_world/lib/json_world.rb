require 'active_support/concern'
require 'active_support/core_ext/object/json'
require 'active_support/core_ext/object/blank'
require 'active_support/json'

module JsonWorld
  module DSL
    extend ActiveSupport::Concern

    included do
      include JsonEncodable
    end

    module ClassMethods
      def property(name, options = {})
        property_pool << Property.new(
          options.merge(name: name)
        )
      end

      def link(name, options = {})
        link_pool << Link.new(
          options.merge(name: name)
        )
      end

      def link_pool
        @link_pool ||= []
      end

      def property_names
        property_pool.map(&:name)
      end

      def property_pool
        @property_pool ||= []
      end

      def to_json_schema
        # should wrap JSON Class
        as_json_schema
      end

      def as_json_schema
        {
          link: link_as_json_schema,
          properties: properties_as_json_schema,
          required: required_property_names
        }.reject { |_key, value| value.blank? }
      end

      private

      def required_property_names
        property_pool.reject(&:optional?).map(&:name)
      end

      def link_as_json_schema
        link_pool.map(&:as_json_schema)
      end

      def properties_as_json_schema
        property_pool.reduce({}) do |result, property|
          result.merge(
            property.name => property.as_json_schema
          )
        end
      end
    end
  end

  class Property
    attr_reader :name

    def initialize(name: nil, **options)
      @name = name
      @options = options
    end

    def as_json_schema
      {
        description: description,
        example: example,
        type: type
      }.reject { |_key, value| value.blank? }
    end

    def optional?
      !!@options[:optional]
    end

    private

    def type
      pritty_types = types.map do |type|
        case
        when type == String
          'string'
        when type == Integer
          'integer'
        when type == Float
          'float'
        when type == Array
          'array'
        when type == Hash
          'hash'
        when type == NilClass
          'null'
        when type == FalseClass || type == TrueClass
          'null'
        end
      end

      pritty_types.length > 2 ? pritty_types : pritty_types.first
    end

    def types
      Array(@options[:type])
    end

    def description
      @options[:description]
    end

    def example
      @options[:example]
    end
  end

  class Link
    def initialize(name: nil, **options)
      @name = name
      @options = options
    end

    def as_json_schema
      {
        title: title,
        href: path
      }.reject { |_key, value| value.blank? }
    end

    private

    def path
      @options[:path]
    end

    def title
      @options[:title] || @name.to_s
    end
  end

  module JsonEncodable
    def as_json(options = {})
      properties(options).as_json(options)
    end

    def properties(options = {})
      names = self.class.property_names
      names.reduce({}) do |hash, name|
        value = send(name)
        hash.merge(name => value)
      end
    end
  end
end

class A
  include JsonWorld::DSL

  attr_reader :id, :name, :b

  property(
    :id,
    example: 1,
    description: 'this is a users\' unique id.',
    type: Integer,
    optional: true
  )

  property(
    :name,
    example: 'name',
    type: [NilClass, TrueClass]
  )

  link(
    :get_user,
    path: '/users/:user_id'
  )

  def initialize(id: nil, name: nil, b: nil)
    @id = id
    @name = name
    @b = b
  end
end

class B
  def initialize(hash: {}, ary: [])
    @hash = hash
    @ary = ary
  end
end

aaa = { page: 'bbb', age: 19 }
bbb = [1, 2, 3, 4, 5]
b = B.new(hash: aaa, ary: bbb).to_json
puts A.new(id: 19, name: 'hoge', b: b).to_json

require 'pp'
pp A.to_json_schema
