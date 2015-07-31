module Handler
  class Base
    def call
      run
    end

    def run
      raise NotImplementedError
    end
  end

  class PlugA < Base
    def run
      p "called in A"
    end
  end
end
