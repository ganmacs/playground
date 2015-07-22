-- main = print $ (Just 2 >>= \x -> return $ x + 1)
div2 :: Int -> Maybe Int
div2 x = if x `mod` 2 == 0 then Just x
         else Nothing

hoge :: Int -> Maybe Int
hoge x = do
  x <- div2 $ x
  return x

printHello = do
  print "hello"
  print "hello"

printHelloWithDo = print "hello" >>= \_ -> print "hello"

pointFree x =
  return x >>= print

ppointFree x = do
  k <- return x
  print k

pppointFree x = print =<< return x

main :: IO ()
main = do
  pppointFree 2
  -- pointFree 10
  -- printHelloWithDo
  -- print $ hoge 15
  -- printHello
  -- print "hoge"
