def eratosthenes(list)
  lim = list.last
  i = 0
  ret = []

  while i * i < lim
    i = list.shift
    ret << i
    list = list.reject { |e| e % i == 0 }
    i = list.first
  end

  ret + list
end

p eratosthenes((2..120).to_a)
