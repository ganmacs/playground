{-# LANGUAGE UnboxedTuples, MagicHash #-}

import GHC.Base
import System.Random

hello1 = unIO $ return 1

addsub x y = (# x + y, x - y #)

-- main = IO $ \s -> (# s, () #)

main' :: State# RealWorld -> (# State# RealWorld, () #)
main' s =
  let (# s1, _ #) = unIO (print "hello") s
      (# s2, _ #) = unIO (print "world") s1
      (# s3, r #) = unIO (print "!!") s1
  in (# s3, r #)

test1 = do
  x <- return 1
  print x

test2 = return 2 >>= \x ->
  print x

test3 = IO $ \s ->
  let (# s1, a #) = unIO (print 3) s
      (# s2, r #) = unIO (print a) s1
  in (# s2, r #)

-- main = test1 >> test2 >> test3

shuffle [] = IO $ \s -> (# s, [] #)
shuffle xs = IO $ \s ->
  let (# s1, n #) = unIO (getStdRandom $ randomR (0, length xs - 1) :: IO Int) s
      (# s2, xs' #) = unIO (shuffle $ take n xs ++ drop (n + 1) xs) s1
  in (# s2, (xs !! n) : xs' #)


test11 = ((return "a" >>= putStr) >>= print)
test12 = return "b" >>= putStr >>= print

-- main = test11 >> test12

-- main = IO $ \s ->
--   let (# s1, xs #) = unIO (shuffle [1..9]) s
--       (# s2, r #) = unIO (print xs) s1
--   in (# s2, r #)

-- main = IO main'

-- main =
--   IO $ \s ->
--   let (# s1, r #) = unIO (print "hello") s
--   in (# s1, r #)

  -- let (# a, b #) = addsub 1 2
  -- print (a, b)

  -- let a = return 1
  -- let a = IO $ \s -> (# s, 1 #)
  -- print =<< a

-- main = do
--   let loop i | i <= 3 = do
--                  print i
--                  loop $ i + 1
--       loop _ = return ()
--   loop 1
