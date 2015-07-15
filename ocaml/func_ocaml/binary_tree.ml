module Tree:
sig
  type 'a tree
  val create : 'a -> 'a tree
  val search : 'a -> 'a tree -> bool
  val insert : 'a -> 'a tree -> 'a tree
  val delete : 'a -> 'a tree -> 'a tree
end
  = struct
    type 'a tree = Nil | Node of 'a * 'a tree * 'a tree

    let create x = Nil

    (* search x *)
    let rec search x = function
      | Nil -> false
      | Node (y, _, _) when x = y -> true
      | Node (y, left, _) when x > y -> search x left
      | Node (y, _, right) -> search x right

    let rec insert x = function
      | Nil -> Node (x, Nil, Nil)
      | Node (y, _, _) as nd when x = y -> nd
      | Node (y, left, right) when x < y -> Node(y, insert x left, right)
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
      | Node (y, Nil, Nil) when x = y -> Nil
      | Node (y, left, Nil) when x = y -> left
      | Node (y, Nil, right) when x = y -> right
      | Node (y, left, right) when x = y -> Node(search_min right, left, delete_min right)
      | Node (y, left, right) -> if x < y then Node (y, (delete x left), right)
                                 else Node (y, left, (delete x right))

    let rec iter f = function
      | Nil -> ()
      | Node (x, left, right) -> iter f left; f x; iter f right
  end
;;
