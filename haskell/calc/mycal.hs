import Control.Monad.State
import GHC.Base((<|>))
import Data.Char

type Result = Either String

type Parser s v = StateT s Result v
type CParser v = Parser String v

runParser = runStateT

genErrorMsg :: String -> CParser a
genErrorMsg str = lift $ Left str

look :: CParser Char
look = do
  x:_ <- get
  return x

item :: CParser Char
item = do
  x:xs <- get
  put xs
  return x

satisfy :: (Char -> Bool) -> CParser Char
satisfy f = do
  a <- item
  if f a then return a else genErrorMsg "Unexpected Char"

cjoin :: CParser a -> CParser a -> CParser [a]
cjoin p1 p2 = do
  a <- p1
  b <- p2
  return [a, b]

select :: CParser a -> CParser a -> CParser a
select = (<|>)

many :: CParser a -> CParser [a]
many f = many1 f <|> return []

many1 :: CParser a -> CParser [a]
many1 f = do
  a <- f
  b <- many f
  return $ a:b

number :: CParser Integer
number = do
  n <- many1 digit
  return $ read n
  where digit = satisfy isDigit

string :: CParser String
string = many1 $ satisfy isAlpha

-- Stmnt = Expr EOF
-- Expr = F { Op F }
-- F = NUM

stmnt :: CParser Integer
stmnt = do
  a <- expr
  eof
  return a

eof :: CParser Char
eof = satisfy (==';')

rep :: CParser Integer -> CParser (Integer -> Integer -> Integer) -> CParser Integer
rep a op' = do
  n <- a
  rep' n
    where rep' n' =
            do { o <- op'; n'' <- a; rep' $ o n' n'' }
            <|> return n'

op :: CParser (Integer -> Integer -> Integer)
op = add <|> sub
  where add = satisfy (=='+') >> return (+)
        sub = satisfy (=='-') >> return (-)

expr :: CParser Integer
expr = factor `rep` op

factor :: CParser Integer
factor = number

run :: String -> IO ()
run str = case runParser stmnt str of
  Left _ -> fail "Parse failed"
  Right (a, _) -> print a

main :: IO ()
main = run "12-1+2-;"
