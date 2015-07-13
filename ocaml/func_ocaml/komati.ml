type term = Plus | Minus | Num of int;;

let calc_expr exp =
  let rec inner a = function
    | [] -> a
    | Plus :: Num x :: xs -> inner (a + x) xs
    | Minus ::  Num x :: xs -> inner (a - x) xs
    | _ -> raise (Failure "calc expr inner")
  in match exp with
     | Num x :: xs -> inner x xs
     | _ -> raise (Failure "calc expr")
;;

let rec print_expr = function
  | [] -> print_string " = 100\n"
  | Num n :: xs -> print_int n; print_expr xs
  | Plus :: xs -> print_string " + "; print_expr xs
  | Minus :: xs -> print_string " - "; print_expr xs
;;

let rec make_expr n expr =
  if n = 10 then
    let ret = List.rev expr in
    if calc_expr ret = 100 then print_expr ret else ()
  else
    match expr with
      Num x :: xs ->
      make_expr (n + 1) ((Num n) :: Plus :: expr);
      make_expr (n + 1) ((Num n) :: Minus :: expr);
      make_expr (n + 1) (Num (x * 10 + n) :: xs)
    | _ -> raise (Failure "make expr")
;;


make_expr 2 [Num 1]
