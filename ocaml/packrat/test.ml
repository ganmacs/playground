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
  value3: () -> int
}

let cache2 = Hashtbl.create 100;;
let memoize key f = if Hashtbl.mem cache2 key then Hashtbl.find key
  else let result = f () in Hashtbl.add cache2 key result; result
;;

let fuga () = memoize 10 fun () -> 10
let hoge () = memoize 10 fun () -> 10

let cache = Hashtbl.create 100;;
let key = { value1 = "asdf"; value2 = ['a'; 'c'; 'c']; value3 = fuga };;
let key2 = { value1 = "asdf"; value2 = ['a'; 'c'; 'c'] value3 = hoge };;

Hashtbl.add cache key "asdfasdf";
key.value3 ();;
Hashtbl.find cache key2
