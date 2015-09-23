open Lazy;;

exception Empty_stream;;

type 'a stream = Nils | Cons of 'a * 'a stream lazy_t;;

let rec intgen low high =
  if low > high then Nils
  else Cons (low, lazy (intgen (low + 1) high))
;;

let rec stream_ref s n =
  match s with
    Nils -> raise Empty_stream
  | Cons (x, _) when n = 1 -> x
  | Cons (_, xs) -> stream_ref (force xs) (n + 1)
;;
