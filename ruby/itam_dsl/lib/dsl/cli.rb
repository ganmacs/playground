require 'dsl/context'
require 'dsl/resources/user'

module DSL
  class CLI
    def initialize(file_path)
      @file_path = file_path
    end

    def call
      load
    end


    private

    def load
      context.instance_eval(file_content, @file_path, 1)
    end

    def context
      @context ||= Context.new
    end


    def file_content
      @file_content ||= File.read(@file_path)
    end
  end
end
