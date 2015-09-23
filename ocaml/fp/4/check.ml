open Syntax
open Eval

let rec tcheck1 = function
  | IntLit(_) -> TInt
  | BoolLit(_) -> TBool
  | Eq(e1, e2) -> begin
      match(tcheck1 e1, tcheck1 e2) with
      | (TInt, TInt) -> TBool
      | (TBool, TBool) -> TBool
      | _ -> failwith "type error in eq"
    end
  | Plus(e1, e2) ->
    begin
      match (tcheck1 e1, tcheck1 e2) with
      | (TInt, TInt) -> TInt
      | _ -> failwith "type error in Plus"
    end
  | If(e1, e2, e3) ->
    begin
      match (tcheck1 e1, tcheck1 e2, tcheck1 e3) with
      | (TBool, TInt, TInt) -> TInt
      | (TBool, TBool, TBool) -> TBool
      | _ -> failwith "type error in If"
    end
  | _ -> failwith "unknown expression"

(* tenv is type env *)
let rec tcheck2 tenv = function
  | Var(s) -> lookup s tenv
  | IntLit(_) -> TInt
  | BoolLit(_) -> TBool
  | Eq(e1, e2) -> begin
      match(tcheck2 tenv e1, tcheck2 tenv e2) with
      | (TInt, TInt) -> TBool
      | (TBool, TBool) -> TBool
      | _ -> failwith "type error in eq"
    end
  | Plus(e1, e2) ->
    begin
      match (tcheck2 tenv e1, tcheck2 tenv e2) with
      | (TInt, TInt) -> TInt
      | _ -> failwith "type error in Plus"
    end
  | If(e1, e2, e3) ->
    begin
      match (tcheck2 tenv e1, tcheck2 tenv e2, tcheck2 tenv e3) with
      | (TBool, TInt, TInt) -> TInt
      | (TBool, TBool, TBool) -> TBool
      | _ -> failwith "type error in If"
    end
  | _ -> failwith "unknown expression"
