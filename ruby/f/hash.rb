hash = { a0: 1, a1: 1, a2: 1, a3: 1, a4: 1, a5: 1 }

v = {}
hash.each do |(k, _)|
  v[k] = 2
end
p v

v1 = hash.reduce({}) do |a, (k, _)|
  a.merge(k => 2)
end
p v1
