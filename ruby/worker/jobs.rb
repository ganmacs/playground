class JobsGenrator
  class MyGem
    attr_writer :installed
    attr_reader :name

    def initialize(name, installed = false)
      @name = name
      @installed = installed
    end

    def installed?
      @installed
    end

    def do_something_heavy_job(worker_num)
      puts "START: #{name} in #{worker_num}"
      a = 10000000.times.reduce(&:+)
      puts "FINISH: #{name} in #{worker_num} #{a}"
      self
    end
  end

  GEMS = %w(rails rake bundler itamae specinfra kaminari rubocop).freeze

  def self.call
    GEMS.map { |j| MyGem.new(j) }
  end
end
