module type MonadRequirements = sig
  type 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t
  val return : 'a -> 'a t
end

module ListM = struct
  type 'a t = 'a list

  let return x = [ x ]
  let bind lst f = List.concat (List.map f lst)
  let (>>=) = bind
  let (>>) ma mb = List.concat (List.map (fun x -> mb) ma)

  let mzero = []
  let mplus = (@)

  let guard = function
    | true -> return ()
    | false -> mzero
end
;;

let inc x = [x + 1];;

let rec range limit =
  if limit = 0 then []
  else limit :: range (limit-1)
;;

let adjacent = [[1; 2];
                [0; 2; 3];
                [0; 1; 4];
                [1; 4; 5];
                [2; 3; 6];
                [3];
                [4]];;

ListM.(
  let next_path = function
    | [] -> raise Not_found
    | x :: xs as lst -> (List.nth adjacent x) >>= fun y ->
      guard (not (List.mem y lst)) >> return (y :: lst) in
  let rec searchM is_goal next_state combine = function
    | [] -> mzero
    | x :: xs ->
      if is_goal x then mplus (return (List.rev x)) (searchM is_goal next_state combine xs)
      else searchM is_goal next_state combine (combine (next_state x) xs) in
  let dfsM start goal =
    searchM (fun x -> List.hd x = goal) next_path (@) [[start]]
  in dfsM 0 6


  (* next_path [1] *)
  (* range 10 >>= fun x -> *)
  (* range 10 >>= fun y -> *)
  (* let z = x + y in *)
  (* return z *)
  (* [1; 2; 3] >>= fun x -> *)
  (* ["a"; "b"; "c"] >>= fun y -> return (x, y) *)
  (* [1; 2; 3] >> ["a"; "b"; "c"] *)

  (* [1; 2; 3; 4] >>= (fun x -> *)
  (*     (if x mod 2 = 0 then [()] else []) >> return x) *)
  (* [1; 2; 3; 4] >>= (fun x -> guard (x mod 2 = 0) >> return x) *)

  (* let permutation n xs = *)
  (*   let rec iter m acc = if m = n then return (List.rev acc) *)
  (*     else xs >>= fun x -> *)
  (*       guard (not (List.mem x acc)) >> iter (1 + m) (x :: acc) *)
  (*   in iter 0 [] *)
  (* in permutation 3 [1; 2; 3; 4] *)
  (* mzero :: [1] *)
  (* mplus [2] [] *)
)
