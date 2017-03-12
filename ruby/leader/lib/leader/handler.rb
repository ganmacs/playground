module Leader
  class Handler
    def hello(parmas)
      Leader.logger.debug("called hello!! in serer")
    end
  end
end
