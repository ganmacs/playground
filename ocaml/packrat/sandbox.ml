(* lazy eval by curry *)
type person = { name : (unit -> string); age : int };;
let create_name s () = print_string "call in create_name\n"; s in
let p = { name = create_name "sample"; age = 19 }  in
p.name ()
;;

(* lazy eval by lazy keyword? *)
type person = { name : string lazy_t ; age : int };;
let create_name s = lazy (print_string "call in create_name\n"; s) in
let p = { name = create_name "sample"; age = 19 }  in
Lazy.force p.name
;;


type key = {
  value1: string;
  value2: char list;
  value3: string -> string
}

(* let cache2 = Hashtbl.create 100;; *)

let cache = Hashtbl.create 100;;

let memoize key f = if Hashtbl.mem cache key then Hashtbl.find cache key
  else let result = f () in print_string "call in memoize"; Hashtbl.add cache key result; result
;;

let fuga key = memoize key (fun () -> "fuga")
let hoge key = memoize key (fun () -> "hoge")

let key = { value1 = "asdf"; value2 = ['a'; 'c'; 'c']; value3 = fuga };;
let key2 = { value1 = "asdf"; value2 = ['a'; 'c'; 'c']; value3 = hoge };;
let key3 = { value1 = ";ljk"; value2 = ['b'; 'd'; 'a']; value3 = hoge };;

Hashtbl.add cache key.value1 "asdfasdf";
key2.value3 key3.value1;;
(* Hashtbl.find cache key.value1;; *)
(* Hashtbl.add cache key2 "sfdasaf"; *)
