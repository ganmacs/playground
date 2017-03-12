module Leader
  class Handler
    def hello(parmas)
      Leader.logger.debug("called hello!! in serer")
      200
    end
  end
end
