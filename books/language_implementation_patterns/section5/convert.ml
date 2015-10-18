type ast =
  | IntLit of int
  | Shift of ast * int
  | Add of ast * ast
  | Mul of ast * ast
;;

let rec visit = function
  | IntLit(x) -> string_of_int x
  | Add(l, r) -> "(+ "  ^ visit(l) ^ " " ^ visit(r) ^ ")"
  | Mul(l, r) -> "(* "  ^ visit(l) ^ " " ^ visit(r) ^ ")"
  | Shift(l, n) -> "(<< "  ^ visit(l) ^ " " ^ string_of_int n ^ ")"

let rec simplfy = function
  | Add(l, r) -> begin
      match simplfy l, simplfy r with
      | IntLit(0), _ -> r
      | _, IntLit(0) ->  l
      | x, y -> Add(x, y)
    end
  | Mul(l, r) -> begin
      match simplfy l, simplfy r with
      | IntLit(0), _ -> l
      | _, IntLit(0) -> r
      | IntLit(1), x -> x
      | x, IntLit(1) -> x
      | IntLit(x), y when x = 2 -> Shift(y, 1)
      | y, IntLit(x) when x = 2 -> Shift(y, 1)
      | x, y -> Mul(x, y)
    end
  | x -> x

let () =
  let a = Add(IntLit(1), IntLit(0)) in
  let b = Mul(IntLit(100), a) in
  let c = Mul(IntLit(2), b) in
  print_string @@ visit @@ simplfy c
