require 'plug/resources/base'

module Plug
  module Resources
    class File < Base
      def call
        'file'
      end
    end
  end
end
