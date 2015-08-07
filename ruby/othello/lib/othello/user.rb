module Othello
  class User
    def initialize(turn, board)
      @turn = turn
      @board = board
    end

    def put
      x, y = gets.chomp.split(' ').map(&:to_i)
      call(x - 1, y - 1)
    end

    def call(x, y)
      if @board.putable?(x, y, @turn)
        @board.set_stone(x, y, @turn)
      else
        puts "{x, y} = {#{x}, #{y}} is invalid."
        put
      end
    end

    def win?
    end
  end
end
