-- http://www.geocities.jp/m_hiroi/func/haskell28.html

import Data.Char
import System.IO

data Value = INT Integer
           | REAL Double deriving (Show, Eq)

data Token = Number Value
           | Ident String
           | Add | Sub | Mul | Div
           | Assign
           | Lpar | Rpar
           | Semic
           | Comma
           | Eof
           | Others Char
           deriving (Show, Eq)

-- build in function
data Func = F1 (Double -> Double)
          | F2 (Double -> Double -> Double)
          | Fi1 (Double -> Integer)

-- ast types
data Expr = Num Value
          | Var String
          | Op1 (Value -> Value) Expr
          | Op2 (Value -> Value -> Value) Expr Expr
          | Agn Expr Expr
          | App Func [Expr]


funcTable :: [(String, Func)]
funcTable = [("sqrt", F1 sqrt),
             ("sin",  F1 sin),
             ("cos",  F1 cos),
             ("tan",  F1 tan),
             ("asin", F1 asin),
             ("acos", F1 acos),
             ("atan", F1 atan),
             ("exp",  F1 exp),
             ("pow",  F2 (**)),
             ("log",  F1 log),
             ("sinh", F1 sinh),
             ("cosh", F1 cosh),
             ("tanh", F1 tanh),
             ("floor",   Fi1 floor),
             ("ceiling", Fi1 ceiling),
             ("round",   Fi1 round),
             ("truncate",Fi1 truncate)]


type Lexer = (Token, String)
type Calc a = Either String a

calcError :: String -> Calc a
calcError = Left

getToken :: String -> Lexer
getToken "" = (Eof, "")
getToken (x:xs)
  | isSpace x = getToken xs
  | isAlpha x = let (s, ys) = span isAlphaNum (x:xs)
                in (Ident s, ys)
  | isDigit x = let (s, ys@(y:_)) = span isDigit (x:xs) -- need semic
                in if y `elem` ".eE"
                   then case reads (x:xs) of
                   [] -> error "not number"
                   [(y', ys')] -> (Number (REAL y'), ys')
                   else (Number (INT (read s)), ys)
  | otherwise =
      case x of
      '=' -> (Assign, xs)
      ',' -> (Comma, xs)
      '+' -> (Add, xs)
      '-' -> (Sub, xs)
      '*' -> (Mul, xs)
      '/' -> (Div, xs)
      '(' -> (Lpar, xs)
      ')' -> (Rpar, xs)
      ';' -> (Semic, xs)
      _ -> (Others x, xs)

lexer :: String -> ([Token], String)
lexer xs =
  let (t, ys) = getToken xs
  in case t of
  Semic -> ([Semic], ys)
  Eof -> ([Eof], ys)
  _ -> let (ts, zs) = lexer ys
       in (t:ts, zs)

expr1 :: [Token] -> Calc (Expr, [Token])
expr1 xs = term xs >>= expr_sub
  where
    opLst = [(Add, add), (Sub, sub)]
    expr_sub zs@(e, y:ys) =
      case lookup y opLst of
      Nothing -> return zs
      Just op -> term ys >>= \(e', ys') -> expr_sub (Op2 op e e', ys')

expr :: [Token] -> Calc (Expr, [Token])
expr xs = expr1 xs >>= expr_sub
  where
    expr_sub (e, Assign:ys) = case e of
      Var _ -> expr ys >>= \(e', ys') -> return (Agn e e', ys')
      _ -> calcError "invalid assing form"
    expr_sub e = return e

factor :: [Token] -> Calc (Expr, [Token])
factor (Number x : xs) = return (Num x, xs)
factor (Lpar : xs) =
  expr xs >>= \(e, y:ys) ->
  case y of
  Rpar -> return (e, ys)
  _ -> calcError "')' expected"
factor (Add : xs) = expr xs     -- e.g. +3
factor (Sub : xs) = expr xs >>= \(e, ys) -> return (Op1 neg e, ys) -- e.g. -3
factor (Ident x : xs) =
  case lookup x funcTable of
  Nothing -> return (Var x, xs)
  Just fn -> getArgs xs >>= \(args, ys) ->
    if (argsNums fn) > (length args)
    then calcError "few number args"
    else return (App fn args, ys)
    where argsNums fn = case fn of
            (F1 _) -> 1
            (F2 _) -> 2
            (Fi1 _) -> 1
factor (Eof : _) = calcError "end of file"
factor (x : _) = calcError ("unexpected Token: " ++ show x)

getArgs :: [Token] -> Calc ([Expr], [Token])
getArgs (Lpar : xs) = iter xs []
  where iter (Rpar : ys) acc = return (reverse acc, ys)
        iter ys acc = expr ys >>= \(e, ys') ->
           case ys' of
           (Comma : ys'') -> iter ys'' (e:acc)
           (Rpar : ys'') -> return (reverse $ e:acc, ys'')
           (y : _) -> calcError $ "unexpected token in argument list: " ++ show y
getArgs xs = calcError $ "'(' expected but, unexpected token received: " ++ show xs


term :: [Token] -> Calc (Expr, [Token])
term xs = factor xs >>= opt_factor
          where
            opLst = [(Mul, mul), (Div, div')]
            opt_factor zs@(e, y:_) =
              case lookup y opLst of
              Nothing -> return zs
              Just op -> factor xs >>= \(e', ys') -> opt_factor (Op2 op e e', ys')

expression :: [Token] -> Calc (Expr, [Token])
expression xs = expr xs >>= \(e, y:ys) ->
  case y of
  Semic ->  return (e, ys)
  _ -> calcError "expression error"


type Env = [(String, Value)]

evalExpr :: Expr -> Env -> Calc (Value, Env)
evalExpr (Num x) env = return (x, env)
evalExpr (Var x) env =
  case lookup x env of
  Nothing -> calcError $ "not in scope: " ++ show x
  Just v -> return (v, env)
evalExpr (Agn (Var name) e2) env = do
  (v, env') <- evalExpr e2 env
  return (v, (name , v):env')
evalExpr (Op1 f expr) env = do
  (v, env') <- evalExpr expr env
  return (f v, env')
evalExpr (Op2 f expr1 expr2) env = do
  (v1, env') <- evalExpr expr1 env
  (v2, env') <- evalExpr expr2 env'
  return (f v1 v2, env')
evalExpr (App fn args) env = do
  (v, env') <- evalExpr (args !! 0) env
  case fn of
    F1 f -> return (REAL (f (toREAL v)), env')
    F2 f -> do
      (v', env'') <- evalExpr (args !! 1) env'
      return (REAL (f (toREAL v) (toREAL v')), env'')
    Fi1 f -> return (INT (f (toREAL v)), env')

toREAL :: Value -> Double
toREAL (INT x) = fromIntegral x
toREAL (REAL x) = x

neg :: Value -> Value
neg (INT x) = INT (- x)
neg (REAL x) = REAL (- x)

add :: Value -> Value -> Value
add (INT x) (INT y) = INT (x + y)
add (REAL x) (REAL y) = REAL (x + y)
add (INT x) (REAL y) = REAL (fromIntegral x + y)
add (REAL x) (INT y)  = REAL (x + fromIntegral y)

sub :: Value -> Value -> Value
sub (INT x) (INT y) = INT (x - y)
sub (REAL x) (REAL y) = REAL (x - y)
sub (INT x) (REAL y) = REAL (fromIntegral x - y)
sub (REAL x) (INT y)  = REAL (x - fromIntegral y)

mul :: Value -> Value -> Value
mul (INT x) (INT y) = INT (x * y)
mul (REAL x) (REAL y) = REAL (x * y)
mul (INT x) (REAL y) = REAL (fromIntegral x * y)
mul (REAL x) (INT y)  = REAL (x * fromIntegral y)

div' :: Value -> Value -> Value
div' (INT x) (INT y) = INT (x `div` y)
div' (REAL x) (REAL y) = REAL (x / y)
div' (INT x) (REAL y) = REAL (fromIntegral x / y)
div' (REAL x) (INT y)  = REAL (x / fromIntegral y)


toplevel :: String -> Env -> IO ()
toplevel xs env = do
  putStr "Calc> "
  let (ys, xs') = lexer xs
  case expression ys of
    Left mes -> do putStrLn mes
                   toplevel xs' env
    Right (e, _) ->
      case evalExpr e env of
        Left mes -> do putStrLn mes
                       toplevel xs' env
        Right (v, env') -> do
          case v of
            INT x -> print x
            REAL x -> print x
          toplevel xs' env'

main :: IO ()
main = do
  xs <- hGetContents stdin
  toplevel xs []
