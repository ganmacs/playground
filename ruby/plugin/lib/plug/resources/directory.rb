require 'plug/resources/base'

module Plug
  module Resources
    class Directory < Base
      def call
        'dicrectory'
      end
    end
  end
end
