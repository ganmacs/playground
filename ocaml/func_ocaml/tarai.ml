(* let rec tarai x y z = *)
(*   if x <= y then y *)
(*   else tarai (tarai (x - 1) y z) (tarai (y - 1) z x) (tarai (z - 1) x y) *)
(* ;; *)

(* print_int (tarai 13 6 0) *)
(* ;; *)

(* momoize tarai *)

(* let table = Hashtbl.create 2048 *)
(* let rec tarai_memo x y z = *)
(*   let key = (x, y, z) in *)
(*   if Hashtbl.mem table key then Hashtbl.find table key *)
(*   else *)
(*     let value = if x <= y then y *)
(*                 else tarai_memo (tarai_memo (x - 1) y z) *)
(*                                 (tarai_memo (y - 1) z x) *)
(*                                 (tarai_memo (z - 1) x y) *)
(*     in Hashtbl.add table key value; *)
(*        value *)
(* ;; *)

(*   print_int (tarai_memo 130 60 0);; *)

let lookup table func key =
  if Hashtbl.mem table key then
    Hashtbl.find table key
  else
    let value = func key in
    Hashtbl.add table key value;
    value
;;

let rec tarai (x, y, z) =
  if x <= y then y
  else memo_tarai (memo_tarai (x - 1, y, z),
                   memo_tarai (y - 1, z, x),
                   memo_tarai (z - 1, x, y))
and memo_tarai =
  let table = Hashtbl.create 2048 in
  fun x -> lookup table tarai x
;;

tarai (12, 6, 0);;

let rec tarai_closure x y z =
  if x <= y then y
  else let zz = z () in
       tarai_closure (tarai_closure (x - 1) y (fun () -> zz))
                     (tarai_closure (y - 1) zz (fun () -> x))
                     (fun () -> (tarai_closure (zz - 1) x (fun () -> y)))
;;
tarai_closure 12 6 (fun () -> 0);;
