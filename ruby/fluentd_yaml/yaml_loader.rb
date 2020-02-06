# Copy from https://github.com/eagletmt/hako/blob/34cdde06fe8f3aeafd794be830180c3cedfbb4dc/lib/hako/yaml_loader.rb

require 'psych'
require 'json'
require 'fluent/config/error'

class YamlLoader

  FluentJSONValue = Struct.new(:val) do
    def to_s
      val.to_json
    end

    def to_element
      to_s
    end
  end

  FluentStringValue = Struct.new(:val, :context) do
    def to_s
      context.instance_eval("\"#{val}\"")
    rescue Fluent::SetNil => _
      ''
    rescue Fluent::SetDefault => _
      ':default'
    end

    def to_element
      to_s
    end
  end

  def initialize(context = Kernel.binding)
    @context = context
    @current_path = nil
  end

  # @param [String] path
  # @return [Hash]
  def load(path)
    class_loader = Psych::ClassLoader.new
    scanner = Psych::ScalarScanner.new(class_loader)

    visitor = Visitor.new(scanner, class_loader)

    visitor._register_domain('tag:include') do |_, val|
      load(path.parent.join(val))
    end

    visitor._register_domain('tag:fluent/json') do |_, val|
      FluentJSONValue.new(val)
    end

    visitor._register_domain('tag:fluent/s') do |_, val|
      FluentStringValue.new(val, @context)
    end

    path.open do |f|
      visitor.accept(Psych.parse(f))
    end
  end

  class Visitor < Psych::Visitors::ToRuby
    INCLUDE_TAG = 'tag:include'
    SHOVEL = '<<'

    def initialize(scanner, class_loader)
      super(scanner, class_loader)
    end

    def _register_domain(name, &block)
      @domain_types.merge!({ name => [name, block] })
    end

    def revive_hash(hash, o)
      super(hash, o).tap do |r|
        if r[SHOVEL].is_a?(Hash)
          h2 = {}
          r.each do |k, v|
            if k == SHOVEL
              h2.merge!(v)
            else
              h2[k] = v
            end
          end
          r.replace(h2)
        end
      end
    end
  end
end
