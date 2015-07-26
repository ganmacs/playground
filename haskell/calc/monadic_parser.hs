import GHC.Base
import Control.Monad.State
import Data.Char

data Parse a = Fail | Err String | Some a deriving Show

instance Functor Parse where
  fmap _ Fail = Fail
  fmap _ (Err s)  = Err s
  fmap f (Some s)  = Some (f s)

instance Applicative Parse where
  pure = Some
  (<*>) _ Fail = Fail
  (<*>) _ (Err s) = Err s
  (<*>) Fail _ = Fail
  (<*>) (Err s) _ = Err s
  (<*>) (Some y) (Some x) = Some (y x)

instance Monad Parse where
  return = Some
  Fail >>= _ = Fail
  Err s >>= _ = Err s
  Some a >>= f = f a
  fail _ = Fail

instance Alternative Parse where
  empty = Fail
  (<|>) Fail ys = ys
  (<|>) ys _ = ys

instance MonadPlus Parse where
  mzero = Fail
  Fail `mplus` ys = ys
  xs `mplus` _ = xs

type Parser s a = StateT [s] Parse a

runParser = runStateT

parseErr :: String -> Parser s a
parseErr s = StateT $ \_ -> Err s

item :: Parser s s
item = do
  (x:xs) <- get
  put xs
  return x

item2 :: Parser s [s]
item2 = do
  x <- item
  y <- item
  return [x, y]

failure :: Parser s a
failure = mzero

-- Check satisfy
sat :: (s -> Bool) -> Parser s s
sat p = do
  x <- item
  if p x then return x else failure

-- select
(+++) :: Parser s a -> Parser s a -> Parser s a
(+++) = mplus

-- zero and over
mmany :: Parser s a -> Parser s [a]
mmany p = many1 p +++ return []

-- one and over
many1 :: Parser s a -> Parser s [a]
many1 p = do
  x <- p
  xs <- mmany p
  return $ x:xs

number :: Parser Char Integer
number = do
  xs <- token $ many1 $ sat isDigit
  return (read xs)

numbers :: Parser Char [Integer]
numbers = many1 $ token number

spaces :: Parser Char String
spaces = mmany $ sat isSpace

token :: Parser Char a -> Parser Char a
token p = do
  a <- p
  spaces
  return a

add, sub, mul, div' :: Parser Char (Integer -> Integer -> Integer)
add = do
  token $ sat ('+'==)
  return (+)
sub = do
  token $ sat ('-'==)
  return (-)
mul = do
  token $ sat ('*'==)
  return (*)
div' = do
  token $ sat ('/'==)
  return div

rep :: Parser Char Integer -> Parser Char (Integer -> Integer ->  Integer) ->  Parser Char Integer
rep p q = do
  a <- p
  rep_sub a
  where
    rep_sub v = do {
      op <- q; v' <- p; rep_sub (op v v')
    } +++ return v

term :: Parser Char Integer
term = factor `rep` (mul +++ div')

expr :: Parser Char Integer
expr = term `rep` (add +++ sub)

factor :: Parser Char Integer
factor =number
        +++ do token $ sat ('('==)
               n <- expr
               n' <- token item
               case n' of
                 ')' -> return n
                 _ -> parseErr "')' expected"
        +++ do token $ sat ('-'==)
               factor
        +++ do token $ sat ('+'==)
               factor

main = print ()
