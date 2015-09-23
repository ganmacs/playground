type exp =
  | IntLit of int
  | Plus of exp * exp
  | Minus of exp * exp
  | Times of exp * exp
  | Div of exp * exp
  | BoolLit of bool
  | If of exp * exp * exp
  | Eq of exp * exp
  | Greater of exp * exp
;;
type value =
  | IntVal  of int
  | BoolVal of bool
;;
IntLit(2);;
Plus(IntLit(1), IntLit(3));;

let a e = Plus(e, IntLit(2));;

a (IntLit 3);;

let rec ab = function
  | IntLit(x) -> if x < 0 then IntLit(-x) else IntLit(x)
  | Plus(x, y) -> Plus(ab x, ab y)
  | Minus(x, y) -> Minus(ab x, ab y)
  | Times(x, y) -> Times(ab x, ab y)
  | Div(x, y) -> Div(ab x, ab y)
;;

ab @@ a (IntLit(-3));;

(* 2-3. 数式の処理 *)

let rec eval1 = function
  | IntLit(x) -> x
  | Plus(x, y) -> (eval1 x) + (eval1 y)
  | Minus(x, y) -> (eval1 x) - (eval1 y)
  | Times(x, y) -> (eval1 x) * (eval1 y)
  | Div(x, y) -> let d = eval1 y in
    if d = 0 then failwith "arithmetic error" else (eval1 x) / d
;;

eval1 @@ a (IntLit(3));;

(* 2-4. 真理値とif の処理 *)
(* eval2: exp -> value *)
let rec eval2 = function
  | IntLit(x) -> IntVal(x)
  | BoolLit(b) -> BoolVal(b)
  | Plus(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(yy)) -> IntVal(xx + yy)
      | _ -> failwith "integer value expected"
    end
  | Minus(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(yy)) -> IntVal(xx - yy)
      | _ -> failwith "integer value expected"
    end
  | Times(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(yy)) -> IntVal(xx * yy)
      | _ -> failwith "integer value expected"
    end
  | Div(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(0)) -> failwith "arithmetic error"
      | (IntVal(xx), IntVal(yy)) -> IntVal(xx / yy)
      | _ -> failwith "integer value expected"
    end
  | Eq(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx = yy)
      | (BoolVal(xx), BoolVal(yy)) -> BoolVal(xx = yy)
      | _ -> failwith "wrong type"
    end
  | If(cond, t, f) -> begin
      match (eval2 cond) with
      | BoolVal(true) -> eval2 t
      | BoolVal(false) -> eval2 f
      | _ -> failwith "wrong type"
    end
  | Greater(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx > yy)
      | _ -> failwith "integer value expected"
    end
;;

eval2 (IntLit 1);;
eval2 (IntLit 11);;
eval2 (Plus (IntLit 1, Plus (IntLit 2, IntLit 11)));;
eval2 (Times (IntLit 1, Plus (IntLit 2, IntLit 11)));;
eval2 (If (Eq(IntLit 2, IntLit 1),
           Times(IntLit 1, IntLit 2),
           Times(IntLit 1, Plus(IntLit 2,IntLit 3))));;
eval2 (Eq (IntLit 1, IntLit 1));;
eval2 (Eq (IntLit 1, IntLit 2));;
eval2 (Eq (BoolLit true, BoolLit true));;
eval2 (Eq (BoolLit true, BoolLit false));;
eval2 (Greater (IntLit 2, IntLit 3))

(* 2-5. 入れ子になった関数定義と高階関数 *)

let rec eval2a e =
  let rec binop f x y =
    match (eval2 x, eval2 y) with
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
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(0)) -> failwith "arithmetic error"
      | (IntVal(xx), IntVal(yy)) -> IntVal(xx / yy)
      | _ -> failwith "integer value expected"
    end
  | Eq(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx = yy)
      | (BoolVal(xx), BoolVal(yy)) -> BoolVal(xx = yy)
      | _ -> failwith "wrong type"
    end
  | If(cond, t, f) -> begin
      match (eval2 cond) with
      | BoolVal(true) -> eval2 t
      | BoolVal(false) -> eval2 f
      | _ -> failwith "wrong type"
    end
  | Greater(x, y) -> begin
      match (eval2 x, eval2 y) with
      | (IntVal(xx), IntVal(yy)) -> BoolVal(xx > yy)
      | _ -> failwith "integer value expected"
    end
;;


eval2a (IntLit 1);;
eval2a (IntLit 11);;
eval2a (Plus (IntLit 1, Plus (IntLit 2, IntLit 11)));;
eval2a (Times (IntLit 1, Plus (IntLit 2, IntLit 11)));;
eval2a (If (Eq(IntLit 2, IntLit 1),
           Times(IntLit 1, IntLit 2),
           Times(IntLit 1, Plus(IntLit 2,IntLit 3))));;
eval2a (Eq (IntLit 1, IntLit 1));;
eval2a (Eq (IntLit 1, IntLit 2));;
eval2a (Eq (BoolLit true, BoolLit true));;
eval2a (Eq (BoolLit true, BoolLit false));;
eval2a (Greater (IntLit 2, IntLit 3))
