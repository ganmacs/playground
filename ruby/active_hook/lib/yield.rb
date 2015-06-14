class Configration
  attr_accessor :page, :max_page, :per_page
end

class Kami
  def self.configure
    yield(@config ||= Configration.new)
  end

  def self.config
    @config
  end

  configure do |conf|
    conf.page = 10
    conf.max_page = 100
    conf.per_page = 5
  end
end

p Kami.config
