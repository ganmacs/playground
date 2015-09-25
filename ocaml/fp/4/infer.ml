open Syntax
open Eval
open Unify

let rec substitute tvar t = function
  | [] -> []
  | (x, t2) :: tenv2 ->
    let t3 = (if t2 = tvar then t else t2) in
    (x, t3) :: (substitute tvar t tenv2)

(* let substitute tvar t = *)
(*   List.map (fun (x, t2) -> (x, if t2 = tvar then t else t2)) *)

let new_typevar s = TVar("'" ^ s)

let rec tinf1 tenv = function
  | IntLit(_) -> (tenv, TInt)
  | BoolLit(_) -> (tenv, TBool)
  | Var(s) ->
    (try
       let t1 = lookup s tenv in
       (tenv, t1)
     with Failure(_) ->
       let tvar = new_typevar s in
       let tenv1 = ext tenv s tvar in
       (tenv1, tvar)
    )
  | Plus(e1, e2) ->
    let (tenv1, t1) = tinf1 tenv e1 in
    let tenv2 = begin
      match t1 with
      | TInt -> tenv1
      | TVar(s) -> substitute t1 TInt tenv1
      | _ -> failwith "type error in Plus"
    end
    in
    let (tenv3, t2) = tinf1 tenv2 e2 in
    let tenv4 = begin
      match t2 with
      | TInt -> tenv3
      | TVar(s) -> substitute t2 TInt tenv3
      | _ -> failwith "type error in Plus"
    end
    in (tenv4, TInt)
  | If(e1, e2, e3) ->
    let (tenv1, t1) = tinf1 tenv e1 in
    let tenv2 = begin
      match t1 with
      | TBool -> tenv1
      | TVar(s) -> substitute t1 TBool tenv1
      | _ -> failwith "type error in If"
    end
    in
    let (tenv3, t2) = tinf1 tenv2 e2 in
    let (tenv4, t3) = tinf1 tenv3 e3 in
    begin
      match (t2, t3) with
      | (TInt, TInt) -> (tenv4, TInt)
      | (TBool, TBool) -> (tenv4, TBool)
      | (TVar(_), TInt) ->
        let tenv5 = substitute t2 TInt tenv4 in (tenv5, TInt)
      | (TInt, TVar(_)) ->
        let tenv5 = substitute t3 TInt tenv4 in (tenv5, TInt)
      | (TVar(_), TBool) ->
        let tenv5 = substitute t2 TBool tenv4 in (tenv5, TBool)
      | (TBool, TVar(_)) ->
        let tenv5 = substitute t3 TBool tenv4 in (tenv5, TBool)
      | (TVar(_), TVar(_)) ->
        let tenv5 = substitute t2 t3 tenv4 in (tenv5, t3)
      | _ -> failwith "type error in IF"
    end
    | _ -> failwith "unimplemnt"

let theta0 = ([]: tysubst)

let new_typevar n = (TVar("'a" ^ (string_of_int(n))), n + 1)

(* tifn2 : tenv -> exp -> int -> tenv * ty * tysubst * int *)
let rec tinf2 tenv exp n = match exp with
  | Var(s) ->
    (try
       let t1 = lookup s tenv in
       (tenv, t1, theta0, n)
     with Failure (_) ->
       let (e, n1) = new_typevar n in
       let tenv1 = ext tenv s e in
       (tenv1, e, theta0, n1)
    )
  | IntLit(_) -> (tenv, TInt, theta0, n)
  | BoolLit(_) -> (tenv, TBool, theta0, n)
  | Plus(e1, e2) ->
    let (tenv1, t1, theta1, n1) = tinf2 tenv e1 n in
    let (tenv2, t2, theta2, n2) = tinf2 tenv1 e2 n1 in
    let t11 = subst_ty theta2 t1 in
    let theta3 = unify [(t11, TInt); (t2, TInt)] in
    let tenv3 = subst_tyenv theta3 tenv2 in
    let theta4 = compose_subst theta3 (compose_subst theta2 theta1) in
    (tenv3, TInt, theta4, n2)
  | Fun(x, e) ->
    let (tx, n1) = new_typevar n in
    let tenv1 = ext tenv x tx in
    let (tenv2, t1, theta1, n2) = tinf2 tenv1 e n1 in
    let t2 = subst_ty theta1 tx in
    let tenv3 = remove tenv2 x in
    (tenv3, TArrow(t2, t1), theta1, n2)
  | App(e1, e2) ->
    let (tenv1, t1, theta1, n1) = tinf2 tenv e1 n in
    let (tenv2, t2, theta2, n2) = tinf2 tenv1 e2 n1 in
    let (tx, n3) = new_typevar n2 in
    let t11 = subst_ty theta2 t1 in
    let theta3 = unify [(t11, TArrow(t2, tx))] in
    let t3 = subst_ty theta3 tx in
    let tenv3 = subst_tyenv theta3 tenv2 in
    let theta4 = compose_subst theta3 (compose_subst theta2 theta1) in
    (tenv3, t3, theta4, n3)
  | _ -> failwith "unknow expression"
