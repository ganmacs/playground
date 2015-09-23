type exp =
  | Var of string         (* variable e.g. x *)
  | IntLit of int         (* integer literal e.g. 17 *)
  | BoolLit of bool       (* boolean literal e.g. true *)
  | If of exp * exp * exp (* if e then e else e *)
  | Let of string * exp * exp   (* let x=e in e *)
  | LetRec of string * string * exp * exp   (* letrec f x=e in e *)
  | Fun of string * exp   (* fun x -> e *)
  | App of exp * exp      (* function application i.e. e e *)
  | Eq of exp * exp       (* e = e *)
  | Greater of exp * exp  (* e > e *)
  | LessGreater of exp * exp  (* e <> e *)
  | Less of exp * exp     (* e < e *)
  | Plus of exp * exp     (* e + e *)
  | Minus of exp * exp    (* e - e *)
  | Times of exp * exp    (* e * e *)
  | Div of exp * exp      (* e / e *)
  | Empty                 (* [ ] *)
  | Match of exp * ((exp * exp) list)    (* match e with e->e | ... *)
  | Cons of exp * exp     (* e :: e *)
  | Head of exp           (* List.hd e *)
  | Tail of exp           (* List.tl e *)

(* 値の型 *)
type value =
  | IntVal  of int        (* integer value e.g. 17 *)
  | BoolVal of bool       (* booleanvalue e.g. true *)
  | ListVal of value list (* list value e.g. [1;2;3] *)
  | FunVal  of string * exp * env
                          (* function value e.g. \x. x+1 with env *)
  | RecFunVal of string * string * exp * env
                          (* recursive function value: solution-1 *)
                          (* let rec f x = e1 in e2 *)
  | RecFunVal2 of string * string * exp * env ref
                          (* recursive function value: solution-2 *)
                          (* let rec f x = e1 in e2 *)
and
  env = (string * value) list

type ty = TInt | TBool | TArrow of ty * ty
