module IdenM = struct
  let return x = x
  let bind x f = f x
  let ( >>= ) = bind
end
;;

let inc x = x + 1;;
let double x = x * 2;;

IdenM.(
  (* inc 10 *)
  (* (return 10 >>= inc) *)

  (* 10 >>= return *)
  (* 10 *)

  (* 10 >>= inc >>= double *)
 10 >>= (fun x -> inc x >>= double)
)
