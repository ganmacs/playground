module Utils
  class Loader
    def initialize(klass, file_path = '')
      @klass = Models.const_get(klass)
      @file_path = file_path
    end

    def all
      @all ||= load_file.map do |o|
        @klass.new(o)
      end
    end

    def find(&block)
      all.find(&block)
    end

    private

    def load_file
      @load_file ||= YAML.load_file(@file_path)
    end
  end
end
