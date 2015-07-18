module MaybeM = struct
  type 'a t = 'a option

  let return x = Some x
  let bind v f = match v with
      None -> None
    | Some x -> f x
  let (>>=) = bind

  let (>>) ma mb = match ma with
      None -> None
    | Some _ -> mb
end
;;

let check a x = if a = x then Some x else None;;

let is_a = check "a";;
let is_b = check "b";;
let is_c = check "c";;
let abc = [is_a; is_b; is_c];;

MaybeM.(
  (* Some 4 >>= (fun x -> Some (x * 4)); *)
  (* Some 4 >>= return; *)
  (* return 4 >>= (fun x -> Some (x + 1)) >>= (fun x -> Some (x * 2)) *)
  (* return 4 >>= (fun x -> (fun y -> Some (y + 1)) x >>= (fun x -> Some (x * 2)) ) *)

  (* let a = "a" and b = "b" and c = "c" in *)
  (* is_a a >>= fun x -> *)
  (* is_b b >>= fun y -> *)
  (* is_c c >>= fun z -> *)
  (* return (x ^ y ^ z) *)

  Some 10 >> Some 9
  (* None >> Some 9 *)
);;
