module Plug
  module Resources
    class Base
      def call
        raise NotImplementedError
      end
    end
  end
end
