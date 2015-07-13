let a = [|10; 20; 30|];;
a.(0);;
a.(0) <- 100;;
a;;


let b = ref "10";;
!b;;
b := "1000";;
b;;


type foo = {mutable bar: int; baz: float};;
let a = { bar = 1; baz = 1.2};;
a.bar <- 100;;
a;;

(* let c = ref [];; *)
(* a := [1; 2; 3];; *)
  (* a;; *)

let fact n =
  let i = ref n and v = ref 1 in
  while !i > 0 do
    v := !i * !v;
    i := !i - 1
  done;
  !v
;;

fact 6;;


let fact2 n =
  let v = ref 1 in
  for i = 2 to n do
    v := !v * i
  done;
  !v
;;

fact2 5;;

let rec comb = function
  | (_, 0)  -> 1
  | (a, b) when a == b -> 1
  | (a, b) -> comb(a-1, b) + comb(a-1, b-1);;

comb(10, 5);;


let pascal x =
  for i = 0 to x do
    for j = 0 to i do
      print_int (comb (i, j));
      print_string " "
    done;
    print_newline ()
  done;
;;

pascal 10;;
