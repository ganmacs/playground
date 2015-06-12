# require 'models/base'

module Models
  class User
    attr_reader :repo, :ip

    def initialize(repo: '', ip: '')
      @repo = repo
      @ip = ip
    end
  end
end
