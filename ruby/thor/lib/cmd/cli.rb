require 'thor'

module Cmd
  class CLI < Thor
    def initialize(args, opts, config)
      super(args, opts, config)
    end

    desc "hello NAME", "say hello to NAME"
    def hello(name)
      puts "Hello #{name}"
    end
  end
end
