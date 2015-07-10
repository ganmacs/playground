let rec insert_sort lst =
  let rec insert x = function
    | [] -> [x]
    | y :: ys as t -> if x < y then x :: t else y :: insert x ys
  in match lst with
     | [] -> []
     | x :: xs -> insert x (insert_sort xs)
;;
insert_sort [9; 1; 8; 2; 7; 3; 6; 4; 5] ;;
