import Control.Monad.State
import GHC.Base((<|>))
import Data.Char

type Result = Either String

type Parser v = StateT String Result v

runParser = runStateT

genErrorMsg :: String -> Parser a
genErrorMsg str = lift $ Left str

look :: Parser Char
look = do
  x:_ <- get
  return x

item :: Parser Char
item = do
  x:xs <- get
  put xs
  return x

satisfy :: (Char -> Bool) -> Parser Char
satisfy f = do
  a <- item
  if f a then return a else genErrorMsg "Unexpected Char"

cjoin :: Parser a -> Parser a -> Parser [a]
cjoin p1 p2 = do
  a <- p1
  b <- p2
  return [a, b]

select :: Parser a -> Parser a -> Parser a
select = (<|>)

many :: Parser a -> Parser [a]
many f = many1 f <|> return []

many1 :: Parser a -> Parser [a]
many1 f = do
  a <- f
  b <- many f
  return $ a:b

number :: Parser Integer
number = do
  n <- many1 digit
  return $ read n
  where digit = satisfy isDigit

string :: Parser String
string = many1 $ satisfy isAlpha

--

-- Stmnt = Expr EOF
-- Expr = F { Op F }
-- F = NUM

match :: (Char -> Bool) -> Parser Char
match f = do
  a <- satisfy f
  space
  return a

stmnt :: Parser Integer
stmnt = do
  a <- expr
  eof
  return a

eof :: Parser Char
eof = satisfy (==';')

rep :: Parser Integer -> Parser (Integer -> Integer -> Integer) -> Parser Integer
rep a op' = do
  n <- a
  rep' n
    where rep' n' =
            do { o <- op'; n'' <- a; rep' $ o n' n'' }
            <|> return n'

op :: Parser (Integer -> Integer -> Integer)
op = add <|> sub
  where add = match (=='+') >> return (+)
        sub = match (=='-') >> return (-)

expr :: Parser Integer
expr = factor `rep` op

factor :: Parser Integer
factor = do
  a <- number
  space
  return a

space :: Parser String
space = many $ satisfy isSpace

run :: String -> IO ()
run str = case runParser stmnt str of
  Left s -> fail s
  Right (a, _) -> print a

main :: IO ()
main = run "12 - 1 + 2;"
