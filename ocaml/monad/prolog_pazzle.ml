open Printf

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

type nation = US | IL | AU;;
type sports = Basket | Cricket | Tennis;;
type name = Michael | Simon | Richard;;
type person = { name : name; rank : int; nation : nation; sports : sports };;

let print_person p =
  let name person =
    match person.name with
      Simon -> "Simon"
    | Michael -> "Michael"
    | Richard -> "Richard" in
  let nation person =
    match person.nation with
      US -> "US"
    | IL -> "IL"
    | AU -> "AU" in
  let sports person =
    match person.sports with
      Basket -> "Basket"
    | Cricket -> "Cricket"
    | Tennis -> "Tennis"
  in print_string ((name p) ^ " " ^ (sports p) ^ " " ^ (nation p) ^ "\n")
;;

let rec find_person_by_nation nation = function
  | [] ->  raise (Failure "find_nation")
  | x :: xs -> if nation = x.nation then x
    else find_person_by_nation nation xs
;;

let rec find_person_by_sports sports = function
  | [] ->  raise (Failure "find_sports")
  | x :: xs -> if sports = x.sports then x else find_person_by_sports sports xs
;;

let is_duplicate p1 p2 = p1.rank = p2.rank ||
                         p1.sports = p2.sports ||
                         p1.nation = p2.nation
;;

let check p1 p2 p3 = is_duplicate p1 p2 ||
                     is_duplicate p2 p3 ||
                     is_duplicate p3 p1
;;

let rec find_p a = function
  | [] -> (print_string "fuga\n"; false)
  | x :: xs -> if a = x.sports then true
    else find_p a xs
;;

ListM.(
  let make_person name =
    [1; 2; 3] >>= fun x ->
    [US; IL; AU] >>= fun y ->
    [Basket; Cricket; Tennis] >>= fun z ->
    return { name = name; rank = x; nation = y; sports = z } in
  let solve =
    make_person Michael >>= fun m ->
    make_person Simon >>= fun s ->
    make_person Richard >>= fun r ->
    guard (not (check m s r)) >>
    guard (m.sports = Basket) >>
    guard (m.nation <> US) >>
    guard (s.nation = IL) >>

    (* [m; s; r] >>= fun x -> *)
    (* guard ((List.hd x).rank < (find_person_by_nation US x).rank ) >> *)

    (* guard (find_p Tennis [m; s; r]) >> *)
    (* guard (s.rank < (find_person_by_sports Tennis [m; s; r]).rank ) >> *)
    (* guard ((find_person_by_sports Cricket [m; s; r]).rank = 1) >> *)
    return [m; s; r]
    (* return [m.sports; s.sports; r.sports] *)

  in solve
  (* in List.length solve *)
);;
