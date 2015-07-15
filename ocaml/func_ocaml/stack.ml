module Stack:
sig
  exception Empty
  type 'a stack
  val create : 'a stack
  val push : 'a stack -> 'a -> 'a stack
  val top : 'a stack -> 'a
  val pop : 'a stack -> 'a stack
  val is_empty : 'a stack -> bool
end
= struct
    exception Empty

    type 'a stack = SNil | SCell of 'a * 'a stack

    (* return Nil stack *)
    let create = SNil

    (*  push x item *)
    let push st x = SCell (x, st)

    (* get top data *)
    let top = function
      | SNil -> raise Empty
      | SCell (x, _) -> x

    let pop = function
      | SNil -> raise Empty
      | SCell (_, xs) -> xs

    let is_empty st = st = SNil
end
