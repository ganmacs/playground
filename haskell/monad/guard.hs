import Control.Monad

hoge :: [Int] -> Bool
hoge [] = error "error"
hoge (x:xs) = if x > 10 then False else hoge xs

solve = do
  a <- [1, 10, 3]
  b <- [4, 11, 6]
  c <- [7, 23, 9]
  guard (hoge [a, b, c])
  return (a, b, c)

main :: IO ()
main = print solve
  -- print $ hoge [1, 2, 3]
