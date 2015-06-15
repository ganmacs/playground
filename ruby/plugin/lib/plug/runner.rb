require 'active_support/core_ext/string/inflections'

module Plug
  class Runner
    def initialize(resouces)
      @resouces = resouces
    end

    def call
      action_classes.map(&:call)
    end

    def action_classes
      @actions ||= @resouces.map do |resouce|
        class_name = resouce.to_s.camelize
        Plug.const_get(class_name, false).new
      end
    end
  end
end
