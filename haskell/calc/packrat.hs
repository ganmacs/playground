import Control.Monad.State
import GHC.Base((<|>))
import Data.Char

type Result = Either String

type Parser s v = StateT s Result v

type Pos = Int
type Key = (String, Pos)

type Env = [(Key, Integer)]

runParser = runStateT

look :: Parser [a] a
look = do
  x:_ <- get
  return x

item :: Parser [a] a
item = do
  x:xs <- get
  put xs
  return x

satisfy :: (a -> Bool) -> Parser [a] a
satisfy f = do
  a <- item
  if f a then return a else mzero

unsatisfy :: (a -> Bool) -> Parser [a] a
unsatisfy f = satisfy (not . f)

cjoin :: Parser [a] a -> Parser [a] a -> Parser [a] [a]
cjoin p1 p2 = do
  a <- p1
  b <- p2
  return [a, b]

select :: Parser [a] a -> Parser [a] a -> Parser [a] a
select = (<|>)

many :: Parser [a] a -> Parser [a] [a]
many f = many1 f <|> return []

many1 :: Parser [a] a -> Parser [a] [a]
many1 f = do
  a <- f
  b <- many f
  return $ a:b

number :: Parser String Integer
number = do
  -- p <- memorize ("number", 10)
  n <- many1 digit
  return $ read n
  where digit = satisfy isDigit

-- memorize :: Key -> Parser String Integer -> Parser Env v
-- memorize key = do
--    env <- get
--    case lookup key env of
--      Just x -> return x
--      Nothing -> return 1

-- memorize key env f = case lookup key env of
--   Just n -> return $ Just n
--   Nothing -> do
--      <- f
--     return a
-- memorize ("add", 10)

main = print $ runParser number "1;"
