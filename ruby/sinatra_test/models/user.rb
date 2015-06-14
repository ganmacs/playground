# require 'models/base'

module Models
  class User
    attr_reader :repo, :ip

    def initialize(repo: nil, ip: nil)
      @repo = repo
      @ip = ip
    end

    def save
      if @repo
        File.open('src/users.data.yml', 'w+') do |f|
          f.write(to_yaml)
        end

        true
      else
        false
      end
    end

    def to_yaml
      {
        repo: @repo,
        ip: @ip
      }
    end
  end
end
