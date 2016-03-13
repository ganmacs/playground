class JobsGenrator
  class MyGem
    attr_writer :installed
    attr_reader :name

    def initialize(name, deps = [], installed = false)
      @name = name
      @deps = deps
      @installed = installed
    end

    def installed?
      @installed
    end

    def dependencies_installed?(all_gems)
      installed_gems = all_gems.select(&:installed?).map(&:name)
      (@deps - installed_gems).empty?
    end

    def do_something_heavy_job(worker_num)
      puts "START: #{name} in #{worker_num}"
      a = sleep 5
      # a = 10000000.times.reduce(&:+)
      puts "FINISH: #{name} in #{worker_num} #{a}"
      self
    end
  end

  GEMS = {
    bundler: [],
    i18n: [],
    json: [],
    arel: [],
    minitest: [],
    activesupport: [:json, :minitest],
    activemodel: [:activesupport],
    activerecord: [:activemodel, :activesupport, :arel],
    rails: [:activerecord, :activemodel, :bundler],
  }

  def self.call
    GEMS.map { |j, deps| MyGem.new(j, deps) }
  end
end
