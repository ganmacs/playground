open Syntax

let rec lookup x env = match env with
  | [] -> failwith ("unbound variable: " ^ x)
  | (k, y) :: env1 -> if k = x then y else lookup x env1

(* 名前がゴミ *)
let rec occurs tx t =
  if tx = t then true
  else
    match t with
    | TArrow(t1, t2) -> (occurs tx t1) || (occurs tx t2)
    | _ -> false

(* 代入theatを型tに適応 *)
let rec subst_ty theta t =
  let rec subst_ty1 theta1 s =
    match theta1 with
    | [] -> TVar(s)
    | (tx, t1) :: theta2 ->
      if tx = s then t1
      else subst_ty1 theta2 s
  in
  match t with
  | TInt -> TInt
  | TBool -> TBool
  | TArrow(t2, t3) -> TArrow(subst_ty theta t2, subst_ty theta t3)
  | TVar(s) -> subst_ty1 theta s

(* compose_subst: tysubst -> tysubst -> tysubst *)
(* 2つの代入を合成した代入を返す *)
let compose_subst theta2 theta1 =
  let theta11 = List.map (fun (type_str, t) -> (type_str, subst_ty theta2 t)) theta1
  in
  List.fold_left (fun tua ->
      fun (tx, t) ->
        try
          let _ = lookup tx theta1 in
          tua
        with Failure (_) ->
          (tx, t) :: tua
    ) theta11 theta2

(* subst_eql: tysubst -> tyenv -> tyenv *)
(* 代入thetaを型の等式のリストeqlを適応する *)
let subst_eql theta eql =
  List.map
    (fun (t1, t2) -> (subst_ty theta t1, subst_ty theta t2))
    eql

(* unify: (ty * ty) list -> tysubst *)
let unify eql =
  let rec solve eql theta =
    match eql with
    | [] -> theta
    | (t1, t2) :: eql2 ->
      if t1 = t2 then solve eql2 theta
      else
        begin
          match (t1, t2) with
          | (TArrow(t11, t12), TArrow(t21, t22)) -> solve ((t11, t12) :: (t21, t22) :: eql2) theta
          | (TVar(s), _) ->
            if (occurs t1 t2)
            then failwith "unification failded"
            else solve (subst_eql [(s, t2)] eql2) (compose_subst [(s, t2)] theta)
          | (_, TVar(s)) ->
            if (occurs t2 t1)
            then failwith "unification failded"
            else solve (subst_eql [(s, t1)] eql2) (compose_subst [(s, t1)] theta)
          | (_, _) -> failwith "unification failded"
        end
  in solve eql []
(* unify [(TVar("'a"), TBool)]  *)
(* TVar("'a") と TBoolが等しいかどうかを判定？ *)
(* 戻り値は [("'a", TBool)] ？  型代入 *)
