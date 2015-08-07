require 'othello/board'
require 'othello/user'
require 'othello/stone'

module Othello
  class Facilitator
    def run
      puts board.to_s
      user1.put
      puts board.to_s
      user2.put
      puts board.to_s
    end

    def winner
      if board.black_stone_size > board.white_stone_size
        user1
      elsif board.black_stone_size < board.white_stone_size
        user2
      else
        puts 'draw'
      end
    end

    private

    def user1
      @user1 ||= Othello::User.new(Stone.white, board)
    end

    def user2
      @user2 ||= Othello::User.new(Stone.black, board)
    end

    def board
      @board ||= Othello::Board.new
    end
  end
end
