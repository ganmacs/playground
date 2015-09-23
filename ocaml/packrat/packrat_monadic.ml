module ParseM = struct

end

module PackratMonadic:
sig
  val eval : string ->  int
end

= struct
  type pos = int

  and ('d, 'v) pparser = Pparser of ('d -> 'v result)

  and 'a result = Parsed of 'a * derivs
                 | NoParse

  and derivs = {
    dv_additive : derivs -> int result;
    dv_multitive : derivs -> int result;
    dv_primary : derivs -> int result;
    dv_decimal : derivs -> int result;
    dv_char : unit -> char result;
    position : pos;
  }

  let cache = Hashtbl.create 10000

  let memorize key f = if Hashtbl.mem cache key then Hashtbl.find cache key
    else let ret = f () in Hashtbl.add cache key ret; ret

  let split str =
    let rec inner acc = function
      | "" -> acc
      | x -> inner ((String.get x 0) :: acc) (String.sub x 1 ((String.length x) - 1))
    in List.rev @@ inner [] str;;

  let dv_additive d = d.dv_additive d
  let dv_multitive d = d.dv_multitive d
  let dv_primary d = d.dv_primary d
  let dv_decimal d = d.dv_decimal d
  let dv_char d = d.dv_char ()

  let rec p_additive d =
    memorize ("addtive", d.position) (fun () ->
        let alt2 () = match dv_multitive d with
          | Parsed (v, d1) -> Parsed (v, d1)
          | NoParse -> NoParse in
        match dv_multitive d with
        | Parsed (vleft, d1) -> (match dv_char d1 with
            | Parsed ('+', d2) -> (match dv_additive d2 with
                | Parsed (vright, d3) -> Parsed (vleft + vright, d3)
                | _ -> alt2 ())
            | _ -> alt2 ())
        | _ -> alt2 ())

  and p_multitive d =
    memorize ("multitive", d.position) (fun () ->
        let alt2 () = match dv_primary d with
          | Parsed (v, d1) -> Parsed (v, d1)
          | NoParse -> NoParse in
        match dv_primary d with
        | Parsed (vleft, d1) -> (match dv_char d1 with
            | Parsed ('*', d2) -> (match dv_multitive d2 with
                | Parsed (vright, d3) -> Parsed (vleft * vright, d3)
                | _ -> alt2 ())
            | _ -> alt2 ())
        | _ -> alt2 ()
      )

  and p_primary d =
    memorize ("primary", d.position) (fun () ->
        let alt2 () =  match dv_decimal d with
          | Parsed (v, d1) -> Parsed (v, d1)
          | NoParse -> NoParse in
        match dv_char d with
        | Parsed ('(', d1)-> (match dv_additive d1 with
            | Parsed (v, d2) -> (match dv_char d2 with
                | Parsed (')', d3) -> Parsed (v, d3)
                | _ -> alt2 ())
            | _ -> alt2 ())
        | _ -> alt2 ()
      )

  and p_decimal d =
    memorize ("decimal", d.position) (fun () ->
        match dv_char d with
        | Parsed ('0', d1) -> Parsed (0, d1)
        | Parsed ('1', d1) -> Parsed (1, d1)
        | Parsed ('2', d1) -> Parsed (2, d1)
        | Parsed ('3', d1) -> Parsed (3, d1)
        | Parsed ('4', d1) -> Parsed (4, d1)
        | Parsed ('5', d1) -> Parsed (5, d1)
        | Parsed ('6', d1) -> Parsed (6, d1)
        | Parsed ('7', d1) -> Parsed (7, d1)
        | Parsed ('8', d1) -> Parsed (8, d1)
        | Parsed ('9', d1) -> Parsed (9, d1)
        | _ -> NoParse
      )

  and p_char lst = (fun () -> match lst with
      | [] -> NoParse
      | x :: xs -> Parsed (x, (parse xs))
    )

  and parse s = {
    dv_additive = p_additive;
    dv_multitive = p_multitive;
    dv_primary = p_primary;
    dv_decimal = p_decimal;
    dv_char = p_char s;
    position = List.length s
  }

  let eval s =
    let char_list = split s in
    let derivs = parse char_list in
    match dv_additive derivs with
    | Parsed (x, rem) -> x
    | _ -> raise (Failure "Parse error");;
end
;;

PackratMonadic.eval("2*(2+6)")
