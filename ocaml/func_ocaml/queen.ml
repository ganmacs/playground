let safe x xs =
  let rec inner i = function
    | [] -> true
    | y :: ys -> if (y + i = x) || (y - i = x) then false
                 else inner (i + 1) ys
  in inner 1 xs
;;

let check_safe = function
  | [] -> true
  | x :: xs -> safe x xs
;;

(* let rec check_safe  = function *)
(*   | [] -> true *)
(*   | x :: xs -> if safe x xs then check_safe xs else false *)
(* ;; *)

let remove x = List.filter (fun y -> not (x = y));;

let rec print_list = function
  | [] -> print_newline ()
  |  x :: xs -> print_int x; print_string " "; print_list xs
;;

(* let rec queen lst ret = *)
(*   if lst = [] then *)
(*     if check_safe ret then print_list ret else () *)
(*   else *)
(*     List.iter (fun x -> queen (remove x lst) (x :: ret)) lst *)
(* ;; *)

let rec queen lst ret =
  if lst = [] then print_list ret
  else
    List.iter (fun x -> if check_safe (x :: ret)
                        then queen (remove x lst) (x :: ret)
                        else ()
              ) lst
;;

queen [1; 2; 3; 4; 5; 6; 7; 8; 9] [];;
