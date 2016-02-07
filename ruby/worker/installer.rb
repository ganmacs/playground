class Installer
  def initialize(size, gems)
    @size = size
    @gems = gems
  end

  def install!
    enqueue
    process
  end

  private

  def enqueue
    raise NotImplementedError
  end

  def process
    raise NotImplementedError
  end
end
