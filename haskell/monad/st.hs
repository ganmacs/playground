{-# LANGUAGE UnboxedTuples #-}

import GHC.Base
import GHC.ST
import Control.Monad
import Control.Monad.ST
import Data.IORef
import Data.STRef
import Data.Array.ST

sum' xs = do
  v <- newIORef 0
  forM_ xs $ \x ->
    modifyIORef v $ (+x)
  readIORef v

sum'' xs = runST $ do
  v <- newSTRef 0
  forM_ xs $ \x ->
    modifySTRef v $ (+x)
  readSTRef v

unST (ST f) = f

main = do
  let arr = runST $ do
        a <- newArray (0, 5) 0 :: ST s (STUArray s Int Int)
        forM_ [0..5] $ \x -> writeArray a x (x + 1)
        getElems a
  print arr

-- main = do
--   let a = return 1 :: ST s Int
--   print =<< stToIO a

-- main = do
--   let f = unST $ return 1
--       (# _, v1 #) = f (realWorld#)
--   print v1

-- main = print =<< sum' [1..100]
-- main = print $ sum'' [1..100]
-- main = do
--   let a = return 1 :: ST s Int
--   print $ runST a

-- main = IO $ \i ->
--   let f1 = unST $ return 1
--       (# s1, r1 #) = f1 i       -- 適用してるし f1は関数 State -> State s a
--       f2 = unIO $ print r1
--       (# s2, r2 #) = f2 s1
--   in (# s2, r2 #)
