{-# LANGUAGE UnboxedTuples #-}

import GHC.Base


io = IO $ \s ->
  let (# s1, v #) = unIO (return 1) s
  in (# s1, v #)

io2 = return 1 :: IO Int

io3 = unIO (return 1 :: IO Int)

io4 k = \i ->
  let (# s, v #) = unIO (return 1 :: IO Int) i
      (# s1, v2 #) = unIO (k v) s
  in (# s1, v2 #)

-- main = print =<< IO (io4 $ \x -> return (x + 1) :: IO Int)

io5 = IO $ \s ->
  let (# s2, v #) = unIO (print  "hello") s
  in (# s2, v #)

-- main = print =<< io5

a `bind` f = IO $ \s ->
  let (# s1, v1 #) = unIO a s
      (# s2, v2 #) = unIO (f v1) s1
  in (# s2, v2 #)

main = return 1 `bind` print
