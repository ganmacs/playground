let adjacent = [
  [1; 2];     (* A *)
  [0; 2; 3];  (* B *)
  [0; 1; 4];  (* C *)
  [1; 4; 5];  (* D *)
  [2; 3; 6];  (* E *)
  [3];        (* F *)
  [1]]        (* G *)
;;

let rec print_path = function
  | [] -> print_newline ()
  | x :: xs -> print_int x; print_string " "; print_path xs
;;

let dfs start goal =
  let rec inner = function
    | [] -> ()
    | n :: _ as l when n = goal -> print_path (List.rev l)
    | n :: _ as path -> List.iter (fun x -> if not (List.mem x path) then inner (x :: path))
                                  (List.nth adjacent n)
  in inner [start]
;;

dfs 0 6;;

let bfs start goal =
  let q = Queue.create () in
  Queue.add [start] q;
  while not (Queue.is_empty q) do
    let path = Queue.take q in
    let p = List.hd path in
    if p = goal then print_path (List.rev path)
    else List.iter (fun x -> if not (List.mem x path) then Queue.add (x :: path) q)
           (List.nth adjacent p)
  done
;;

  bfs 0 6;;

  (* 反復深化 *)
let rec ids goal start limit =
  let rec inner n = function
    | [] -> ()
    | x :: _ as l when (n = limit) && (x = goal) -> print_path (List.rev l)
    | x :: _ as path -> List.iter (fun n -> if not (List.mem n path) then inner (n + 1) (n :: path))
                                  (List.nth adjacent x)
  in inner 1 [start]
;;

print_string "_____________________";;

ids 0 6 1;;
ids 0 6 3;;
ids 0 6 4;;
ids 0 6 6;;
