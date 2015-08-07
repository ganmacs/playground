require 'othello/board'
require 'othello/facilitator'

module Othello
  EMPTY =  0
  WHITE =  1
  BLACK = -1

  class << self
    def run
      facilitator.run
    end

    def facilitator
      @facilitator ||= Othello::Facilitator.new
    end
  end
end
