-- http://d.hatena.ne.jp/kazu-yamamoto/20080920/1221881130

import Control.Monad
import GHC.Base
import Data.Char
import Control.Arrow(first)

data Parser a = Parser (String -> [(a, String)])

instance Functor Parser where
  fmap f ma = Parser $ \str -> map (first f) $ parse ma str

instance Applicative Parser where
  pure = return
  (<*>) fm ma = Parser $ \str -> let a = parse ma str -- [(a,s)]
                                     ff = parse fm str -- [(a,s)] -> [(b,s)]
                                 in concatMap (\(f, _) -> map (first f) a) ff

instance Monad Parser where
  return a = Parser $ \s -> [(a, s)]
  p >>= f = Parser $ \s ->
    concatMap (\(v, s') -> parse (f v) s') $ parse p s

instance Alternative Parser where
  empty = Parser $ const []
  (<|>) xs ys = Parser $ \x -> case parse xs x of
    [] -> parse ys x
    (y:_) -> [y]

instance MonadPlus Parser where
  mzero = Parser $ const []
  mplus p q = Parser $ \x -> parse p x ++ parse q x

parse :: Parser s -> String -> [(s, String)]
parse (Parser p) = p

item :: Parser Char
item = Parser $ \cs -> case cs of
  [] -> []
  (x:xs) -> [(x, xs)]

satisfy :: (Char -> Bool) -> Parser Char
satisfy f = do
  c <- item
  if f c then return c else mzero

mmany :: Parser a -> Parser [a]
mmany p = many1 p <|> return []

many1 :: Parser a -> Parser [a]
many1 p = do
  a <- p
  as <- mmany p
  return $ a:as

char :: Char -> Parser Char
char c = satisfy (==c)

string :: String -> Parser String
string "" = return ""
string (x:xs) = do
  char x
  string xs
  return $ x:xs

number :: Parser Integer
number = token $ do
  n <- many1 digit
  return $ read n
  where digit = satisfy isDigit

chain1 :: Parser a -> Parser (a -> a -> a) -> Parser a
chain1 p op = do
  x <- p
  rest x
  where rest y = do f <- op
                    z <- p
                    rest (f y z)
                 <|> return y

expr :: Parser Integer
expr = do
  op <- unary
  n <- term `chain1` addop
  return $ op n

term :: Parser Integer
term = factor `chain1` mulop

factor :: Parser Integer
factor = number <|> do
  symb "("
  a <- expr
  symb ")"
  return a

addop :: Parser (Integer -> Integer -> Integer)
addop = add <|> sub
  where add = symb "+" >> return (+)
        sub = symb "-" >> return (-)

mulop :: Parser (Integer -> Integer -> Integer)
mulop = mul <|> div'
  where mul = symb "*" >> return (*)
        div' = symb "/" >> return div

unary :: Parser (Integer -> Integer)
unary = plus <|> minus <|> return id
  where plus = symb "+" >> return id
        minus = symb "-" >> return negate

space :: Parser String
space = mmany $ satisfy isSpace

token :: Parser a -> Parser a
token p = do
  a <- p
  space
  return a

symb :: String -> Parser String
symb s = token $ string s

apply :: Parser a -> String -> [(a, String)]
apply p = parse $ do { space; p }

main :: IO ()
main = print $ apply expr "- ( 10 * 11 ) + 19 / 10"
