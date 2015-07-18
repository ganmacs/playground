let rec fib_scp n count =
  if n = 1 || n = 0 then count 1
  else fib_scp (n-1) (fun x -> fib_scp (n-2) (fun y -> count (x + y)))
;;

fib_scp 5 (fun x -> x);;
