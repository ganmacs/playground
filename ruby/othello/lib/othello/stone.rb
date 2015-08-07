module Othello
  attr_reader :color

  class Stone
    EMPTY =  0
    WHITE =  1
    BLACK = -1

    class << self
      def black
        new(BLACK)
      end

      def white
        new(WHITE)
      end
    end

    def initialize(color = EMPTY)
      @color = color
    end

    def flip
      @color *= -1
    end

    def ==(other)
      # fail if other.color == EMPTY
      other.color == @color
    end

    def empty?
      @color == EMPTY
    end

    def black!
      @color = BLACK
    end

    def white!
      @color = WHITE
    end

    def to_s
      case @color
      when WHITE
        ' o |'
      when BLACK
        ' x |'
      else
        '   |'
      end
    end
  end
end
