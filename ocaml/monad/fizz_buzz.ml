(* module type Monad = sig *)
(*   type 'a m *)
(*   val return : 'a -> 'a m *)
(*   val (>>=) : 'a m -> ('a -> 'b m) -> 'b m *)
(* end *)

module FizzBuzzM = struct
  type 'a m = FB of 'a * string
  let return x = FB (x, "")
  let bind (FB (i, s)) f = let FB (j, s2) = f i in FB (j, s ^ s2)
  let (>>=) = bind
end

module FizzBuzz = struct
  open FizzBuzzM

  let fizz x = if x mod 3 = 0 then FB (x, "fizz") else FB (x, "")
  let buzz x = if x mod 5 = 0 then FB (x, "buzz") else FB (x, "")

  let fizzbuzz x = (fizz x) >>= buzz

  let print = function
    | FB (x, "") -> print_int x
    | FB (x, s) -> print_string s
end
;;

open FizzBuzz;;
print @@ fizzbuzz 15
