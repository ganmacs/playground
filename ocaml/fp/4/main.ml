open Syntax
open Eval

let parse str =
  Parser.main Lexer.token
    (Lexing.from_string str)

let rec pretty_print = function
  | IntVal(x)  -> string_of_int x
  | BoolVal(x) -> string_of_bool x
  | ListVal(list) ->
    print_string "[ ";
    List.iter (fun x -> pretty_print x ;  print_string "; ") list;
    print_string " ]"; "failed"
  | FunVal(sym, body, env)  -> "failed"
  | RecFunVal(s, sym, body, env) -> "failed"
  | RecFunVal2(s, sym, body, env) -> "failed"

let run s =
  let env = emptyenv () in
  pretty_print (eval3 (parse s) env)

(* let () = parse "let x = 3 + 1 * 4 in fun y -> x + y";  print_string "s";; *)

(* 使用例は以下の通り。parse関数は Mainモジュールにはいっているので
   open Main;; parse "...";; とするか Main.parse "...";;
   として呼びだす。

$ ./miniocaml
      Objective Caml version 3.09.1

# Main.parse "let x = 3 + 1 * 4 in fun y -> x + y";;
- : Syntax.exp =
Syntax.Let ("x",
 Syntax.Plus (Syntax.IntLit 3,
  Syntax.Times (Syntax.IntLit 1, Syntax.IntLit 4)),
 Syntax.Fun ("y", Syntax.Plus (Syntax.Var "x", Syntax.Var "y")))
#  Main.parse "1 + 2 * 3 ";;
 Main.run "1 + 2 * 3 ";;
- : Syntax.exp =
Syntax.Plus (Syntax.IntLit 1,
 Syntax.Times (Syntax.IntLit 2, Syntax.IntLit 3))
#
*)
