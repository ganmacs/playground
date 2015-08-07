require 'othello/stone'

module Othello
  class Board
    def initialize(n = 8)
      @n = n
      setup
    end

    # set stone and
    def set_stone(x, y, turn)
      board[x][y] = turn
      around_each do |xx, yy|
        if (pos = position_of_same_color_stone(x, y, xx, yy, turn))
          set_line(x, y, pos[0], pos[1], turn, xx, yy)
        end
      end
    end

    def black_stone_size
      count_stone(:black)
    end

    def white_stone_size
      count_stone(:white)
    end

    def putable?(x, y, turn)
      empty?(x, y) && takabble?(x, y, turn)
    end

    def to_s
      ret = [header]

      board.each_with_index do |col, i|
        str = "#{i + 1} |"      # row index
        col.each do |e|
          str += e.to_s
        end
        ret << str
      end

      ret
    end

    private

    def header
      (1..@n).reduce('   ') { |a, e| a + " #{e}  " }
    end

    def count_stone(color)
      b.select { |e| e.send("#{color}?") }.size
    end

    def around_each
      dx = [1, 1, 1, 0, 0, -1, -1, -1]
      dy = [1, 0, -1, -1, 1, 1, 0, -1]

      dx.zip(dy).each do |xx, yy|
        yield(xx, yy)
      end
    end

    def position_of_same_color_stone(x, y, dx, dy, turn)
      x += dx
      y += dy

      if board[x][y] == (-1 * turn)
        position_of_same_color_stone(x, y, dx, dy, turn)
      elsif board[x][y] == turn
        [x, y]
      else
        nil
      end
    end

    def set_line(x, y, nx, ny, turn, dx, dy)
      until (x + dx == nx) && (y + dy == ny)
        board[x + dx][y + dy] = turn
        x += dx
        y += dy
      end
    end

    def empty?(x, y)
      board[x][y].empty?
    end

    def takabble?(x, y, turn)
      around_each do |xx, yy|
        return true if check(x, y, xx, yy, turn)
      end
      false
    end

    def check(x, y, dx, dy, turn)
      x += dx
      y += dy

      if board[x][y] == (-1 * turn)
        check(x, y, dx, dy, turn)
      elsif board[x][y] == turn
        true
      else
        false
      end
    end

    def setup
      c = @n / 2
      board[c - 1][c - 1].white!
      board[c][c].white!
      board[c - 1][c].black!
      board[c][c - 1].black!
    end

    # @return [Array(Array(Int))]
    def board
      @board ||= generate_board
    end

    def generate_board
      Array.new(@n) { Array.new(@n) { Othello::Stone.new } }
    end
  end
end
