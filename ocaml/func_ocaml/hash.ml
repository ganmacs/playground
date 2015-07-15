module type ITEMTYPE =
  sig
    type t
    val hash_size : int
    val hash_func : t -> int
    val equal : t -> t ->  bool
  end

module MakeHash (Item: ITEMTYPE) :
sig
  type t = Item.t
  type 'a hash
  val create : unit -> 'a hash
  val insert : t -> 'a -> 'a hash -> unit
  val search : t -> 'a hash -> 'a option
  val delete : t -> 'a hash -> unit
  val iter : (t -> 'a -> unit) -> 'a hash -> unit
end
  = struct
    type t = Item.t
    type 'a pair = { key : t; mutable value: 'a }
    type 'a hash = Hash of 'a pair list array

    (* Find pair form list *)
    (* @return [pair option] *)
    let rec find k = function
      | [] -> None
      | ({key = x; value = _} as p) :: _ when Item.equal x k -> Some p
      | _ :: xs -> find k xs

    (* Get position in array by calculate hash number *)
    let position key = (Item.hash_func key) mod Item.hash_size

    (* Create Empty hash  *)
    let create () = Hash (Array.make Item.hash_size [])

    (* Insert new pair in hash *)
    let insert k v (Hash (table)) =
      let n = position k in
      match find k table.(n) with
        None -> table.(n) <- {key = k; value = v} :: table.(n)
      | Some p -> p.value <- v

    let search k (Hash (table)) =
      let n = position k in
      match find k table.(n) with
        None -> None
      | Some p -> Some p.value

    let delete k (Hash (table)) =
      let n = position k in
      match find k table.(n) with
        None -> raise Not_found
      | Some p -> table.(n) <- List.filter (fun x -> x <> p) table.(n)

    let iter f (Hash (table)) =
      for n = 0 to Item.hash_size-1 do
        List.iter (fun {key = k; value = v} -> f k v) table.(n)
      done
  end
;;

module StringItem = struct
    type t = string
    let hash_size = 199
    let hash_func key =
      let rec string_hash n a =
        if String.length key = n then a
        else string_hash (n + 1) (a + int_of_char key.[n])
      in string_hash 0 0
    let equal x y = x = y
  end
;;

module StringHash = MakeHash(StringItem)
