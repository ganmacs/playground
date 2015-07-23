import Control.Monad
import Control.Applicative

genList :: [Int]
genList = 1 : 2 : return 3

-- main = print genList
-- main = print $ [3] >>= replicate 3
-- main = print $ join [[1, 2], [3]]

inc :: Monad m => Int -> m Int
inc x = return $ x + 1

incA :: Int -> Int
incA = (+ 1)

test x = do
  a <- [x]
  return $ a + 1

testM = do
  a <- [1, 2, 3]
  b <- inc a
  return $ b * 10

sampleMap = do
  a <- [1 .. 10]
  b <- [1 .. a]
  return $ show b

genPair :: [(Int, Char)]
genPair = do
  join $ join $ forM [1..3] $ \x -> forM "abc" $ \y -> return (x, y)

return' x = [x]
a `bind` f = foldr ((++) .f) []  a

-- main = do
--   print $ [1..3] `bind` \x -> "abc" `bind` \y -> return' (x, y)

listComprehension = do
  a <- [1 .. 5]
  b <- [1 .. 5]
  guard (a + b == 6)
  return (a, b)

main = print listComprehension



-- main = print $ [1..3] `bind` \x -> "abc" `bind` \y -> return' (x, y)

-- main = do
--   print $ do
--     x <- [1..3]
--     y <- "abc"
--     return (x, y)

-- main = print $ sampleMap
  -- print $ forM [1, 3, 4] $ (\x -> [x + 1])
  -- print $ testM

  -- print $ inc =<< (return 1 :: [Int])
  -- print $ inc =<< [1]
  -- print $ incA <$> (return 1 :: [Int])
  -- print $ join [[13, 3], [23]]

  -- print =<< inc =<< return 1

  -- a <- return 1
  -- print a
  -- print =<< return 2

  -- print $ (return 1 :: [] Int)
  -- print $ (return 1 :: [Int])
  -- a <- ([1, 2] :: [Int])
  -- print a
