type s = int

let positive_number i = if (i > 0) then Type.Option(i) else Type.Nothing

let print_opt = function
 | Type.Nothing -> print_string "none\n"
 | Type.Option(i) -> print_int i
