type exp =
  | IntLit of int
  | Plus of exp * exp
  | Minus of exp * exp
  | Times of exp * exp
  | Div of exp * exp
  | BoolLit of bool
  | If of exp * exp * exp
  | Eq of exp * exp
  | Var of string
  | Let of string * exp * exp
  | Greater of exp * exp
;;

type value =
  | IntVal  of int
  | BoolVal of bool
;;

let emptyenv () = [];;

let ext env x y = (x, y) :: env;;

let rec lookup x env = match env with
  | [] -> failwith ("unbound variable: " ^ x)
  | (k, y) :: env1 -> if k = x then y else lookup x env1
;;

let env = ext (emptyenv ()) "x" (IntVal 1);;
let env2 = ext env "x" (IntVal 2);;
lookup "x" env2;;

let print_env env =
  print_string "[";
  let pp = function
    | IntVal(z) -> print_int z
    | BoolVal(z) -> print_string (if z then "true" else "else")
  in
  List.iter
    (fun (x, y) ->
       print_string (x ^ ": ");
       pp y;
       print_string ", ";
    ) env;
  print_string "]\n"
;;

let rec eval3 e env =
  print_env env;
  let rec binop f x y =
    match (eval3 x env, eval3 y env) with
    | (IntVal(xx), IntVal(yy)) -> IntVal(f xx yy)
    | _ -> failwith "integer value expected"
  in
  match e with
  | IntLit(x) -> IntVal(x)
  | BoolLit(b) -> BoolVal(b)
  | Plus(x, y) -> binop (+) x y
  | Minus(x, y) -> binop (-) x y
  | Times(x, y) -> binop ( * ) x y
  | Div(x, y) -> begin
      match (eval3 x env, eval3 y env) with
      | (IntVal(xx), IntVal(0)) -> failwith "arithmetic error"
      | (IntVal(xx), IntVal(yy)) -> IntVal(xx / yy)
      | _ -> failwith "integer value expected"
    end
  | Eq(x, y) -> begin
      match (eval3 x env, eval3 y env) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx = yy)
      | (BoolVal(xx), BoolVal(yy)) -> BoolVal(xx = yy)
      | _ -> failwith "wrong type"
    end
  | If(cond, t, f) -> begin
      match (eval3 cond env) with
      | BoolVal(true) -> eval3 t env
      | BoolVal(false) -> eval3 f env
      | _ -> failwith "wrong type"
    end
  | Greater(x, y) -> begin
      match (eval3 x env, eval3 y env) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx > yy)
      | _ -> failwith "integer value expected"
    end
  | Let(sym, value, e) -> let new_env = ext env sym (eval3 value env) in eval3 e new_env
  | Var(x) -> lookup x env
;;

let e = emptyenv ();;

(* eval3 (Let("x", IntLit 3, Plus(IntLit 3, Var "x"))) e;; *)
eval3 (Let("x", IntLit 3, Let("x", IntLit 5, (Var  "x")))) e;;
