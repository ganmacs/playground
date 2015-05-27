require "active_support/concern"
require "active_support/core_ext/object/json"
require "active_support/json"

module JSON
  module Encodable
    extend ActiveSupport::Concern

    def as_json(options = nil)
      properties(options).as_json(options)
    end

    private

    def properties(options = nil)
      if options
        # anything to do
      end

      names = self.class.property_names
      names.reduce({}) do |hash, name|
        value = send(name)
        hash.merge(name => value)
      end
    end

    module ClassMethods
      def property(property_name)
        property_names << property_name
      end

      def property_names
        @property_names ||= []
      end
    end
  end
end

class A
  include JSON::Encodable

  property :id

  def id
    100
  end

  def name
    'name is '
  end
end

p A.new.to_json
