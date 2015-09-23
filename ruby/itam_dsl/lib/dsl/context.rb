module DSL
  class Context
    def method_missing(method, *args, &block)
      klass = build(method)
      obj = klass.new

      super(method, *args, &block) if klass.nil?
    end

    private

    def to_capital(str)
      str.split('_').map(&:capitalize).join
    end

    def build(class_name)
      Resources.const_get(to_capital(class_name.to_s))
    rescue NameError
      abort 'unknow resouces'
    end
  end
end
