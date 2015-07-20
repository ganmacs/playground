module A = struct
  type 'a m = FB of 'a

  let create x = FB x
  let print (FB a) = print_int a
end
;;

module B = struct
  open A
  let create2 x = create x
end
;;

module C = struct
  include A
  let create2 x = create x
end
;;

module D = struct
  include A

  let print_str (FB a) = print_string a
end
;;

(* signature *)
module type T  = sig
  type 'a m

  val create : 'a -> 'a m
  val print : int m -> unit
end

module AA: T = struct
  type 'a m = FB of 'a
  let create x = FB x
  let print (FB a) = print_int a
end
;;

module E = struct
  open A

  let print_str (FB a) = print_string a
  let print_e x = print x
  let create_e x = FB x
end
;;

(* open A;; *)
(* create 10;; *)

(* include B;; *)
(* create2 1;; *)
open E;;
print_str (create_e "asdf");;
print_e (create_e 2)
