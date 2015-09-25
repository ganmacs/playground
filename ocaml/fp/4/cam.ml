type cam_instr =
  | CAM_Ldi of int
  | CAM_Ldb of bool
  | CAM_Access of int           (* load env stack *)
  | CAM_Closure of cam_code
  | CAM_Apply
  | CAM_Return
  | CAM_Let
  | CAM_EndLet
  | CAM_Test of cam_code * cam_code
  | CAM_Add
  | CAM_Sub
  | CAM_Time
  | CAM_Eq
  | CAM_Less
and cam_code = cam_instr list

type cam_value =
  | CAM_IntVal of int
  | CAM_BoolVal of bool
  | CAM_ClosVal of cam_code *  cam_env
and cam_stack = cam_value list
and cam_env = cam_value list


let rec runner env stack = function
  | [] -> (env, stack)
  | CAM_Ldi(x) :: c -> runner env (CAM_IntVal(x) :: stack) c
  | CAM_Ldb(x) :: c -> runner env (CAM_BoolVal(x) :: stack) c
  | CAM_Access(x) :: c -> runner env ((List.nth env x) :: stack) c
  | CAM_Closure(c1) :: c -> runner env (CAM_ClosVal(c1, env) :: stack) c
  | CAM_Apply :: c -> begin
      match stack with
      | CAM_ClosVal(c1, e) :: v :: s -> runner (v :: CAM_ClosVal(c1, e) :: e) (CAM_ClosVal(c, env) :: s) c1
      | _ -> failwith "Invalid argument in CAM_Apply"
    end
  | CAM_Return :: c -> begin
      match stack with
      | v :: CAM_ClosVal(c1, e) :: s -> runner e (v :: s) c1
      | _ -> failwith "Invalid argument in CAM_Return"
    end
  | CAM_Let :: c -> begin
      match stack with
      | v :: s -> runner (v :: env) s c
      | _ -> failwith "Invalid argument in CAM_Let"
    end
  | CAM_EndLet :: c ->  begin
      match env with
      | _ :: e -> runner e stack c
      | _ -> failwith "Invalid argument in CAM_EndLet"
    end
  | CAM_Test(c1, c2) :: c -> begin
      match stack with
      | CAM_BoolVal(true) :: s -> runner env s (c1 @ c)
      | CAM_BoolVal(false) :: s -> runner env s (c2 @ c)
      | _ -> failwith "Invalid argument in CAM_test"
    end
  | CAM_Add :: c -> begin
      match stack with
      | CAM_IntVal(n1) :: CAM_IntVal(n2) :: s -> runner env (CAM_IntVal(n1 + n2) :: s) c
      | _ -> failwith "Invalid arguments in CAM_Add"
    end
  | CAM_Sub :: c -> begin
      match stack with
      | CAM_IntVal(n1) :: CAM_IntVal(n2) :: s -> runner env (CAM_IntVal(n1 - n2) :: s) c
      | _ -> failwith "Invalid arguments in CAM_Add"
    end
  | CAM_Time :: c -> begin
      match stack with
      | CAM_IntVal(n1) :: CAM_IntVal(n2) :: s -> runner env (CAM_IntVal(n1 * n2) :: s) c
      | _ -> failwith "Invalid arguments in CAM_Add"
    end
  | CAM_Less :: c -> begin
      match stack with
      | CAM_IntVal(n1) :: CAM_IntVal(n2) :: s -> runner env (CAM_BoolVal(n1 < n2) :: s) c
      | _ -> failwith "Invalid arguments in CAM_Add"
    end
  | CAM_Eq :: c -> begin
      match stack with
      | CAM_IntVal(n1) :: CAM_IntVal(n2) :: s -> runner env (CAM_BoolVal(n1 = n2) :: s) c
      | _ -> failwith "Invalid arguments in CAM_Eq"
    end

let cam_interpreter code = match runner [] [] code with
  | (_, ret :: _) -> ret
  | _ -> failwith "おあｋしい"

(* Cam.runner [] [] [CAM_Ldi(4); CAM_Ldi(3); CAM_Ldi(2); CAM_Ldi(1); CAM_Add; CAM_Add; CAM_Add] *)
(* Cam.cam_interpreter [CAM_Ldi(4); CAM_Ldi(3); CAM_Less] *)
(* Cam.runner [] [] [CAM_Ldi(4); CAM_Ldi(3); CAM_Ldi(2); CAM_Ldi(1); CAM_Add; CAM_Times; CAM_Add] *)
