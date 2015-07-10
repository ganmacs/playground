let perm_list n list =
  let remove n = List.filter (fun x -> x <> n) in
  let rec gen_perm_list n xs cur ret =
    if n == 0 then cur :: ret
    else List.fold_right (fun x acc -> gen_perm_list (n-1) (remove x xs) (x :: cur) acc) xs ret
  in gen_perm_list n list [] []
;;

perm_list 2 [1; 2; 3];;

let combination n list =
  let rec comb n lst cur ret =
    match (n, lst) with
      (0, _) -> cur :: ret
    | (_, []) -> raise Not_found
    | (_, x :: xs) when n == List.length lst -> (cur @ lst) :: ret
    | (_, x :: xs) -> comb (n-1) xs (x :: cur) (comb n xs cur ret)
  in comb n list [] [];;

combination 3 [1; 2; 3; 4; 5];;
