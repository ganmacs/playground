let rec flatten lst count =
  match lst with
    [] -> count []
  | x :: _ when x = [] -> []
  | x :: xs -> flatten xs (fun y -> count(x @ y))
;;

flatten [[1; 2]; [3; 4]; [5; 6]] (fun x -> x);;
