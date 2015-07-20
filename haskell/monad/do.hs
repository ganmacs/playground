-- main = print $ (Just 2 >>= \x -> return $ x + 1)
div2 :: Int -> Maybe Int
div2 x = if x `mod` 2 == 0 then Just x
         else Nothing

hoge :: Int -> Maybe Int
hoge x = do
  x <- div2 $ x
  return x

main :: IO ()
main = do
  print $ hoge 15
