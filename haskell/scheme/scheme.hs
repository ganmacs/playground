-- import Control.Monad.Error
import Control.Monad.Except
import Data.Char
import System.IO
import qualified Data.Map as M

-- S Expression types
data SExpr = INT Integer
           | REAL Double
           | SYM String
           | STR String
           | CELL SExpr SExpr
           | NIL
           | PRIM (SExpr -> Scm SExpr)
           | SYNT (GEnv -> LEnv -> SExpr -> Scm (SExpr, GEnv))
           | CLOS SExpr LEnv

-- Evalator
type Scm a = Either String a

-- Local Env
type LEnv = [(String, SExpr)]

-- Global Env
type GEnv = M.Map String SExpr

showCell :: SExpr -> String
showCell (CELL s1 s2) =
  show s1 ++ cdrCell where
    cdrCell = case s2 of
      NIL -> ""
      INT x -> " . " ++ show x
      REAL x -> " . " ++ show x
      STR x -> " . " ++ x
      SYM x -> " . " ++ x
      _ -> " " ++ showCell s2
showCell x = show x

instance Show SExpr where
  show (INT x)  = show x
  show (REAL x) = show x
  show (SYM x)  = x
  show (STR x)  =  x
  show NIL = "()"
  show xs = "(" ++ showCell xs ++ ")"

-- parse error type
data ParseErr = ParseErr String String deriving Show

-- instance Except ParseErr where
--   noMsg = ParseErr "" ""
--   strMsg = ParseErr ""

noMsg = ParseErr "" ""
strMsg = ParseErr ""

type Parser a = Either ParseErr a

-- Read S Expr
isAlpha' :: Char -> Bool
isAlpha' = (`elem` "!$%&*+-/:<=>?@^_~")

isIdent0 :: Char -> Bool
isIdent0 x = isAlpha x || isAlpha' x

isIdent1 :: Char -> Bool
isIdent1 x = isAlphaNum x || isAlpha' x

isREAL :: Char -> Bool
isREAL = (`elem` ".eE")

isNUM :: String -> Bool
isNUM (x:_) = isDigit x
isNUM _ = False

quote :: SExpr
quote = SYM "quote"

getNumber :: String -> Parser (SExpr, String)
getNumber xs = let (y, ys) = span isDigit xs
                in if not (null y) && isREAL (head ys)
                   then case reads xs of
                          [] -> throwError noMsg
                          [(y', ys')] -> return (REAL y', ys')
                   else return (INT (read y), ys)

readSExpr :: String -> Parser (SExpr, String)
readSExpr [] = throwError $ strMsg "EOF"
readSExpr (x:xs)
  | isSpace x = readSExpr xs
  | isDigit x = getNumber (x:xs)
  | isIdent0 x = if x == '+' && isNUM xs
                 then getNumber xs
                 else if x == '-' && isNUM xs
                      then do (y, ys) <- getNumber xs
                              case y of
                                INT z -> return (INT (- z), ys)
                                REAL z -> return (REAL (- z), ys)
                      else
                        let (y, ys) = span isIdent1 (x:xs)
                        in return (SYM y, ys)
  | otherwise =
    case x of
    '(' -> readCell 0 xs
    ';' -> readSExpr $ dropWhile (/= '\n') xs
    '"' -> case reads (x:xs) of
      [] -> throwError $ noMsg
      [(y, ys)] -> return (STR y, ys)
    '\'' ->  do (y, ys) <- readSExpr xs
                return (CELL quote (CELL y NIL), ys)
    _ -> throwError $ ParseErr xs ("unexpected token: " ++ show x)


readCell :: Int -> String -> Parser (SExpr, String)
readCell _ [] = throwError $ strMsg "EOF"
readCell n (x:xs)
  | isSpace x = readCell 0 xs
  | otherwise =
    case x of
    ')' -> return (NIL, xs)
    '.' -> if n == 0
           then throwError $ ParseErr xs "invalid dotted list"
           else do (e, ys) <- readSExpr xs
                   case dropWhile isSpace ys of
                     (')':zs) -> return (e, zs)
                     _ -> throwError $ ParseErr xs "invalid dotted list"
    '(' -> do (y, ys) <- readCell 0 xs
              (y', ys') <- readCell 1 ys
              return (CELL y y', ys')
    _ -> do (y, ys) <- readSExpr (x:xs)
            (y', ys') <- readCell 1 ys
            return (CELL y y', ys')

eval :: GEnv -> LEnv -> SExpr -> Scm (SExpr, GEnv)
eval genv _ NIL = return (NIL, genv)
eval genv _ v@(INT _) = return (v, genv)
eval genv _ v@(REAL _) = return (v, genv)
eval genv _ v@(STR _) = return (v, genv)
eval genv lenv (SYM name) =
  case lookup name lenv of
  Nothing -> case M.lookup name genv of
    Nothing -> throwError $ strMsg $ "unbound variable: " ++ name
    Just v ->  return (v, genv)
  Just v -> return (v, genv)
eval genv lenv (CELL fun args) = do
  (v, genv1) <- eval genv lenv fun
  case v of
    SYNT f -> f genv1 lenv args
    _ -> do (vs, genv2) <- evalArguments genv1 lenv args
            apply genv2 lenv v vs

evalArguments :: GEnv -> LEnv -> SExpr -> Scm (SExpr, GEnv)
evalArguments genv _ NIL = return (NIL, genv)
evalArguments genv lenv (CELL expr rest) = do
  (v1, genv1) <- eval genv lenv expr
  (v2, genv2) <- evalArguments genv1 lenv rest
  return (CELL v1 v2, genv2)
evalArguments _ _ _ = throwError $ strMsg "invalid funcito form"

apply :: GEnv -> LEnv -> SExpr -> SExpr -> Scm (SExpr, GEnv)
apply genv _ func actuals =
  case func of
  PRIM f -> do v <- f actuals
               return (v, genv)
  CLOS (CELL params body) lenv0 -> do
    lenv1 <- makeBindings lenv0 params actuals
    evalBody genv lenv1 body

makeBindings :: LEnv -> SExpr -> SExpr -> Scm LEnv
makeBindings lenv NIL _ = return lenv
makeBindings lenv (SYM name) rest = return $ (name, rest):lenv
makeBindings lenv (CELL (SYM name) rest) (CELL v actuals') =
  makeBindings ((name, v):lenv) rest actuals' -- check
makeBindings _ _ NIL = throwError $ strMsg "error"
makeBindings _ _ _ = throwError $ strMsg "invalid arguments form"

evalBody :: GEnv -> LEnv -> SExpr -> Scm (SExpr, GEnv)
evalBody genv lenv (CELL expr NIL) = eval genv lenv expr
evalBody genv lenv (CELL expr rest) = do
  (_, genv1) <- eval genv lenv expr
  evalBody genv1 lenv rest
evalBody _ _ _ = throwError $ strMsg "invalid arguments form"

true :: SExpr
true = SYM "ture"

false :: SExpr
false = SYM "false"

instance Eq SExpr where
  INT x == INT y = x == y
  REAL x == REAL y = x == y
  STR x == STR y = x == y
  NIL == NIL = True
  _ == _ = False

eq' :: SExpr -> Scm SExpr
eq' (CELL x (CELL y _)) = if x == y then return true else return false
eq' _ = throwError $ strMsg "invalid arguments form"

equal' :: SExpr -> Scm SExpr
equal' (CELL x (CELL y _)) =
  if iter x y then return true else return false
  where iter (CELL a b) (CELL c d) = iter a c && iter b d
        iter a b = a == b
equal' _ = throwError $ strMsg "invalid arguments form"

-- evalQuote :: GEnv -> LEnv -> SExpr -> Scm (SExpr, GEnv)
-- evalQuote genv lenf (CELL expr _)

-- Primitive
car :: SExpr -> Scm SExpr
car NIL = throwError $ strMsg $ "car : NIL"
car (CELL a _) = return a

cdr :: SExpr -> Scm SExpr
cdr NIL = throwError $ strMsg $ "cdr : NIL"
cdr (CELL _ b) = return b

cons :: SExpr -> SExpr -> Scm SExpr
cons NIL NIL= throwError $ strMsg $ "cons : NIL"
cons NIL _= throwError $ strMsg $ "cons : NIL"
cons _ NIL= throwError $ strMsg $ "cons : NIL"
cons a b = return $ CELL a b


initGEnv :: GEnv
initGEnv = M.fromList [("true", true),
                       ("false", false),
                       ("eq?",    PRIM eq'),
                       ("equal?", PRIM equal'),
                       ("car",    PRIM car),
                       ("cdr",    PRIM cdr)
                       ]

repl :: GEnv -> LEnv -> String -> IO ()
repl genv lenv xs = do
  putStr "Scm> "
  hFlush stdout
  case readSExpr xs of
    Left (ParseErr xs' mes) -> do putStrLn mes
                                  repl genv lenv $ dropWhile (/= '\n') xs'
    Right (expr, xs') -> do case eval genv lenv expr of
                              Left mes -> do putStrLn mes
                                             repl genv lenv xs'
                              Right (v, genv1) -> do print v
                                                     repl genv1 lenv xs'


main :: IO ()
main = do
  xs <- hGetContents stdin
  repl initGEnv [] xs



-- main = print $ ()
