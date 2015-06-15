require 'active_support/core_ext/string/inflections'

module Plug
  class Runner
    def initialize(resouces)
      @resouces = resouces
    end

    def call
      resources_classes.map(&:call)
    end

    def resources_classes
      @resources_classes ||= @resouces.map do |resouce|
        class_name = resouce.to_s.camelize
        next unless available_resouces.include?(class_name.to_sym)

        Resources.const_get(class_name, false).new
      end.compact
    end

    def available_resouces
      @available_resouces ||= Resources.constants
    end
  end
end
