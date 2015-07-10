let rec insert_sort lst =
  let rec insert x = function
    | [] -> [x]
    | y :: ys as t -> if x < y then x :: t else y :: insert x ys
  in match lst with
     | [] -> []
     | x :: xs -> insert x (insert_sort xs)
;;
insert_sort [9; 1; 8; 2; 7; 3; 6; 4; 5] ;;

let rec quick_sort = function
  | [] -> []
 | x :: xs -> let (l, r) = List.partition (fun y -> x > y) xs in
              quick_sort l @ [x] @ quick_sort r
;;

quick_sort [5; 3; 7; 6; 9; 8; 1; 2; 4];;

(* tail recur ver. *)

let rec partition f l r = function
  | [] -> (l, r)
  | x :: xs -> if (f x)
               then partition f (x :: l) r xs
               else partition f l (x :: r) xs
;;

let rec quick_sort = function
  | [] -> []
 | x :: xs -> let (l, r) = partition (fun y -> x > y) [] [] xs in
              quick_sort l @ [x] @ quick_sort r
;;
quick_sort [5; 3; 7; 6; 9; 8; 1; 2; 4];;
