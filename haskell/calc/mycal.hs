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

-- Stmnt = Expr ';'
-- Expr = Factor { Op1 Factor }
-- Factor = Term { Op2 Term }
-- Term = NUM | '(' Expr ')'

token :: (Char -> Bool) -> Parser Char
token f = do
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

op1, op2 :: Parser (Integer -> Integer -> Integer)
op1 = add <|> sub
  where add = token (=='+') >> return (+)
        sub = token (=='-') >> return (-)
op2 = mul <|> div'
  where mul = token (=='*') >> return (*)
        div' = token (=='/') >> return div

expr :: Parser Integer
expr = term `rep` op1

term :: Parser Integer
term = factor `rep` op2

factor :: Parser Integer
factor = do { a <- number; space; return a}
         <|> do { s '('; a <- expr; s ')'; return a}
         where s c = token (==c)

space :: Parser String
space = many $ satisfy isSpace

run :: String -> IO ()
run str = case runParser stmnt str of
  Left s -> fail s
  Right (a, _) -> print a

main :: IO ()
main = run "( 1 + 2 ) * 2;"
