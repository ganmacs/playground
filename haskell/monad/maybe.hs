import Control.Applicative
import Data.Maybe
import Data.Char
import Control.Monad

fib 0 = Just 0
fib 1 = Just 1
fib n | n > 1 = (+) <$> fib (n-1) <*> fib (n-2)
      | otherwise = Nothing

bind (Just x) f = f x
bind Nothing f = Nothing

fact :: Int -> Maybe Int
fact 0 = Just 1
fact n | n > 0 = (n*) <$> fact (n-1)
       | otherwise = Nothing

facts :: Int -> Maybe (Int, Int, Int)
facts n = do
  a <- fact n
  b <- fact $ n - 1
  c <- fact $ n - 2
  return (a, b, c)


facts2 n = ( map fact [n, n-1, n-2]
           , mapMaybe' fact [n, n-1, n-2]
           )


-- mapMaybe' f [] = []
-- mapMaybe' f (x:xs) = case f x of
--   Just x -> x : mapMaybe' f xs
--   Nothing -> mapMaybe' f xs

mapMaybe' f = foldr (\x acc ->  case f x of
                       Just x -> x:acc
                       Nothing -> acc
                       )  []


numUpper :: Int -> Int -> String -> Maybe String
-- numUpper x y str = do
--   guard $ length str == x + y
--   guard $ length (filter isDigit $ take x str) == x
--   guard $ length (filter isUpper $ drop x str) == y
--   return str

numUpper x y str = do
  guard $ length str == x + y
  guard $ length (filter isDigit $ take x str) == x
  guard $ length (filter isUpper $ drop x str) == y
  return str

check str = do
  guard $ length str >= 3
  do
    guard $ isDigit $ str !! 0
    guard $ isUpper $ str !! 1
    <|> do
    guard $ isUpper $ str !! 0
    guard $ isLower $ str !! 1
  guard $ isLower $ str !! 2
  Just str

main = do
    print $ check "1"
    print $ check "2Ab"
    print $ check "Abc"
    print $ check "Ab1"
    print $ check "1AB"

-- main = do
--     print $ numUpper 3 2 "123AB"
--     print $ numUpper 3 2 "123ABC"
--     print $ numUpper 3 2 "12ABC"


-- main = do
--   print $ facts 3
--   print $ facts 2
--   print $ facts 1
--   print $ facts 0

--   print $ facts2 3
--   print $ facts2 2
--   print $ facts2 1
--   print $ facts2 0

  -- print $ Just 3 `bind` \a -> Just $ (1*a)
  -- print $ fib (-1)
  -- print $ fib 6
