-- http://www.geocities.jp/m_hiroi/func/haskell31.html

import Data.Char
import System.IO
import Control.Monad.State
import Control.Monad.Error

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

type Calc s a = StateT s (Either String) a

data Func = F1 (Value -> Calc Env Value)
          | F2 (Value -> Value -> Calc Env Value)

data Expr = Num Value
          | Var String
          | Op1 (Value -> Value) Expr
          | Op2 (Value -> Value -> Value) Expr Expr
          | Agn Expr Expr
          | App Func [Expr]

type Env = [(String, Value)]

type Lexer = (Token, String)

callf1 :: (Double -> Double) -> Value -> Calc Env Value
callf1 f v = return $ REAL (f $ toREAL v)

callf2 :: (Double -> Double -> Double) -> Value -> Value -> Calc Env Value
callf2 f v1 v2 = return $ REAL (f (toREAL v1) (toREAL v2))

callfri1 :: (Double -> Integer) -> Value -> Calc Env Value
callfri1 f v = return $ INT (f $ toREAL v)

callfii1 :: (Integer -> Integer) -> Value -> Calc Env Value
callfii1 f (INT x) = return $ INT (f x)
callfii1 _ _ = calcError "Args is not Integer"

callfii2 :: (Integer -> Integer -> Integer) -> Value -> Value -> Calc Env Value
callfii2 f (INT x) (INT y) = return $ INT (f x y)
callfii2 _ _ _ = calcError "Args is not Integer"

item :: Calc [a] a
item = do
  x:xs <- get
  put xs
  return x

lookahead :: Calc [a] a
lookahead = do
  x:_ <- get
  return x

calcError :: String -> Calc s a
calcError msg = throwError (strMsg msg)

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

funcTable :: [(String, Func)]
funcTable = [("sqrt", F1 (callf1 sqrt)),
             ("sin",  F1 (callf1 sin)),
             ("cos",  F1 (callf1 cos)),
             ("tan",  F1 (callf1 tan)),
             ("asin", F1 (callf1 asin)),
             ("acos", F1 (callf1 acos)),
             ("atan", F1 (callf1 atan)),
             ("exp",  F1 (callf1 exp)),
             ("pow",  F2 (callf2 (**))),
             ("log",  F1 (callf1 log)),
             ("sinh", F1 (callf1 sinh)),
             ("cosh", F1 (callf1 cosh)),
             ("tanh", F1 (callf1 tanh)),
             ("floor",   F1 (callfri1 floor)),
             ("ceiling", F1 (callfri1 ceiling)),
             ("round",   F1 (callfri1 round)),
             ("truncate",F1 (callfri1 truncate)),
             -- ("fact",    F1 (callfii1 fact)),
             -- ("comb", F2 (callfii2 comb)),
             ("mod",  F2 (callfii2 mod)),
             ("gcd",  F2 (callfii2 gcd)),
             ("lcm",  F2 (callfii2 lcm))]

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

factor :: Calc [Token] Expr
factor = do
  x <- item
  case x of
    Number v -> return (Num v)
    Lpar -> do e <- expr
               y <- item
               case y of
                 Rpar -> return e
                 _ -> calcError "')' expected"
    Sub -> do e <- expr
              return (Op1 neg e)
    Add -> return =<< expr
    Eof -> calcError "')' expected"
    Ident v ->
      case lookup v funcTable of
        Nothing -> return $ Var v
        Just fn -> do
          args <- getArgs
          if argsNums fn > length args
            then calcError "few number args"
            else return (App fn args)
          where argsNums fn = case fn of
                  (F1 _) -> 1
                  (F2 _) -> 2
    _ -> calcError $ "unexpected token: " ++ show x

getArgs :: Calc [Token] [Expr]
getArgs = do
  v <- item
  case v of
    Lpar -> iter []
            where iter acc = do x <- expr
                                y <- item
                                case y of
                                  Comma -> iter $ x:acc
                                  Lpar -> iter . reverse $ x:acc
                                  _ -> calcError $ "unexpected token in argument list: " ++ show y
    _ ->  calcError $ "'(' expected but, unexpected token received: " ++ show v


rep :: Calc [Token] Expr -> [(Token, Value -> Value -> Value)] -> Calc [Token] Expr
rep p opList = do
  e <- p
  iter e
  where iter e = do
          y <- lookahead
          case lookup y opList of
            Nothing -> return e
            Just op -> do item
                          e' <- p
                          return (Op2 op e e')


term :: Calc [Token] Expr
term = factor `rep` [(Mul, mul), (Div, div')]

expr1 :: Calc [Token] Expr
expr1 = term `rep` [(Add, add), (Sub, sub)]

expr :: Calc [Token] Expr
expr = do
  ee <- expr1
  expr_sub ee
  where expr_sub e = do
          y <- lookahead
          case y of
            Assign -> case e of
                        Var _ -> do item
                                    e' <- expr
                                    return (Agn e e')
                        _ -> calcError "invalid assing form"
            _ -> return e

expression :: Calc [Token] Expr
expression = do
  e <- expr
  y <- lookahead
  case y of
    Semic -> return e
    _ -> calcError "expression error"

evalExpr :: Expr -> Calc Env Value
evalExpr (Num x) = return x
evalExpr (Var x) = do
  env <- get
  case lookup x env of
    Nothing -> calcError $ "not in scope: " ++ show x
    Just v -> return v
evalExpr (Agn (Var name) e2) = do
  env <- get
  v <- evalExpr e2
  put $ (name, v):env
  return v
evalExpr (Op1 f expr) = do
  v <- evalExpr expr
  return $ f v
evalExpr (Op2 f expr1 expr2) = do
  v1 <- evalExpr expr1
  v2 <- evalExpr expr2
  return $ f v1 v2
evalExpr (App fn args)  = do
  v <- evalExpr (args !! 0)
  case fn of
    F1 f ->  f v
    F2 f -> do
      v' <- evalExpr (args !! 1)
      f v v'

toplevel :: String -> Env -> IO ()
toplevel xs env = do
  putStr "Calc> "
  let (ys, xs') = lexer xs
  case runStateT expression ys of
    Left mes -> do putStrLn mes
                   toplevel xs' env
    Right (e, _) ->
      case runStateT (evalExpr e) env of
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
