def merge_sort(list)
  return list if list.size <= 1

  pivot = list.shift
  smaller, greater = list.partition { |e| e < pivot }
  merge_sort(smaller) + [pivot] + merge_sort(greater)
end

list = Array.new(10) { rand(100) }
p list
p merge_sort(list)
