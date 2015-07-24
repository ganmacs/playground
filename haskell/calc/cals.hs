import Data.Char
import Control.Monad.Instances
import System.IO

data Value = INT Integer
           | REAL Double deriving (Show, Eq)

data Token = Number Value
           | Add | Sub | Mul | Div
           | Lpar | Rpar
           | Semic
           | Eof
           | Others Char
           deriving (Show, Eq)

type Lexer = (Token, String)

getToken :: String -> Lexer
getToken "" = (Eof, "")
getToken (x:xs)
  | isSpace x = getToken xs
  | isDigit x = let (s, ys@(y:_)) = span isDigit (x:xs) -- need semic
                in if y `elem` ".eE"
                   then case reads (x:xs) of
                   [] -> error "not number"
                   [(y', ys')] -> (Number (REAL y'), ys')
                   else (Number (INT (read s)), ys)
  | otherwise =
      case x of
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

-- ast types
data Expr = Num Value
          | Op1 (Value -> Value) Expr
          | Op2 (Value -> Value -> Value) Expr Expr

type Calc a = Either String a

--  expr  = term { ("+" | "-"), term }.
--  term  = factor { ("*" | "/"), factor }.
-- factor = num | ("+" | "-"), factor | "(" expr ")".

calcError :: String -> Calc a
calcError = Left

factor :: [Token] -> Calc (Expr, [Token])
factor (Number x : xs) = return (Num x, xs)
factor (Lpar : xs) = expr xs >>= \(e, y:ys) ->
  case y of
  Rpar -> return (e, ys)
  _ -> calcError "')' expected"
factor (Add : xs) = expr xs     -- e.g. +3
factor (Sub : xs) = expr xs >>= \(e, ys) -> return (Op1 neg e, ys) -- e.g. -3
factor (Eof : _) = calcError "end of file"
factor (x : _) = calcError ("unexpected Token: " ++ show x)

term :: [Token] -> Calc (Expr, [Token])
term xs = factor xs >>= opt_factor
          where
            opLst = [(Mul, mul), (Div, div')]
            opt_factor zs@(e, y:_) =
              case lookup y opLst of
              Nothing -> return zs
              Just op -> factor xs >>= \(e', ys') -> opt_factor (Op2 op e e', ys')

expr :: [Token] -> Calc (Expr, [Token])
expr xs = term xs >>= expr_sub
  where
    opLst = [(Add, add), (Sub, sub)]
    expr_sub zs@(e, y:ys) =
      case lookup y opLst of
      Nothing -> return zs
      Just op -> term ys >>= \(e', ys') -> expr_sub (Op2 op e e', ys')

expression :: [Token] -> Calc (Expr, [Token])
expression xs = expr xs >>= \(e, y:ys) ->
  case y of
  Semic ->  return (e, ys)
  _ -> calcError "expression error"

evalExpr :: Expr -> Value
evalExpr (Num x) = x
evalExpr (Op1 op x) = op (evalExpr x)
evalExpr (Op2 op x y) = op (evalExpr x) (evalExpr y)

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

toplevel :: String -> IO ()
toplevel xs = do
  putStrLn "Calc> "
  let (ys, xs') = lexer xs
  case expression ys of
    Left mes -> do putStrLn mes
                   toplevel xs'
    Right (e, _) -> do case evalExpr e of
                         INT x -> print x
                         REAL x -> print x
                       toplevel xs'

main :: IO ()
main = do
  xs <- getContents
  toplevel xs
