module Othello
  class User
    def initialize(turn, board)
      @turn = turn
      @board = board
    end

    def put
      x, y = gets.chomp.split(' ').map(&:to_i)
    rescue NoMethodError
      puts 'detect invalid input. please input'
      put
    ensure
      call(x - 1, y - 1)
    end

    def call(x, y)
      if @board.putable?(x, y, @turn)
        @board.set_stone(x, y, @turn)
      else
        puts "{x, y} = {#{x + 1}, #{y + 1}} is invalid."
        put
      end
    end

    def win?
    end
  end
end
