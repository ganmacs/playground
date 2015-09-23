require 'dsl/resources/base'

module DSL
  module Resources
    class User < Base
      attr_reader :username
      attr_reader :password
      attr_reader :home
    end
  end
end
