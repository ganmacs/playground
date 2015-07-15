module type ItemType =
  sig
    type t
    val compare : t -> t -> int
  end
;;

module MakeTree(Item: ItemType) = struct

    (* tree type *)
    type tree = Nil | Node of Item.t * tree * tree

    let create = Nil

    let rec search x = function
      | Nil -> None
      | Node (y, _, _) when Item.compare x y = 0 -> Some y
      | Node (y, left, _) when Item.compare x y < 0 -> search x left
      | Node (y, _, right) -> search x right

    let rec insert x = function
      | Nil -> Node (x, Nil, Nil)
      | Node (y, _, _) as nd when Item.compare x y = 0 -> nd
      | Node (y, left, right) when Item.compare x y < 0 -> Node(y, insert x left, right)
      | Node (y, left, right) -> Node(y, left, insert x right)

    let rec search_min = function
      | Nil -> raise Not_found
      | Node(x, Nil, _) -> x
      | Node(_, left, _) -> search_min left

    let rec delete_min = function
      | Nil -> raise Not_found
      | Node(x, Nil, _) -> Nil
      | Node(x, left, right) -> Node(x, delete_min left, right)

    let rec delete x = function
      | Nil -> raise Not_found
      | Node (y, Nil, Nil) when Item.compare x y = 0 -> Nil
      | Node (y, left, Nil) when Item.compare x y = 0 -> left
      | Node (y, Nil, right) when Item.compare x y = 0 -> right
      | Node (y, left, right) when Item.compare x y = 0 -> Node(search_min right, left, delete_min right)
      | Node (y, left, right) -> if Item.compare x y < 0 then Node (y, (delete x left), right)
                                 else Node (y, left, (delete x right))

    let rec iter f = function
      | Nil -> ()
      | Node (x, left, right) -> iter f left; f x; iter f right
  end
;;
