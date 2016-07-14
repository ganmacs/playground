class BSearch
  def self.run(ary, t)
    r = ary.size - 1
    l = 0
    while l < r
      pp = (r + l) / 2

      case
      when ary[pp] > t
        r = pp - 1
      when ary[pp] == t
        puts "Found #{pp}"
        return 1
      when ary[pp] < t
        l = pp + 1
      end
    end
  end
end

class BSearchTest
  def self.run
    puts 'Search 3 in 1 - 100'
    BSearch.run((1..100).to_a, 3)

    puts 'Search 101 in 1 - 100'
    BSearch.run((1..100).to_a, 101)

    puts 'Search 2 in 1 - 200 by 2'
    BSearch.run((1..200).select { |e| e % 2 == 0 }.to_a, 2)

    puts 'Search 3 in 1 - 100 by 2'
    BSearch.run((1..200).select { |e| e % 2 == 0 }.to_a, 3)
  end
end

BSearchTest.run
