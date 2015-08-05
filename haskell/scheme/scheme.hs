import Control.Monad.Error
import Data.Char

-- S Expression types
data SExpr = INT Integer
           | REAL Double
           | SYM String
           | STR String
           | CELL SExpr SExpr
           | NIL

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

instance Error ParseErr where
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
                                (INT x) -> return (INT (- x), ys)
                                (REAL x) -> return (REAL (- x), ys)
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
              return ((CELL y y'), ys')
    _ -> do (y, ys) <- readSExpr (x:xs)
            (y', ys') <- readCell 1 ys
            return ((CELL y y'), ys')

main = print $ ()
