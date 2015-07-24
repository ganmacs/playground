-- http://qiita.com/7shi/items/4a8a2807bb5186576c61

import Control.Monad
import System.Random
import Data.IORef
import Data.Array.IO

randomPlus1 = do
  a <- newIORef =<< (getStdRandom $ randomR (0, 9) :: IO Int)
  modifyIORef a (+1)
  print =<< readIORef a

modifyArray ary i f = writeArray ary i =<< f <$> readArray ary i
fixArray = do
  a <- newArray (0, 2) 0 :: IO (IOUArray Int Int)
  print =<< getElems a
  modifyArray a 1 (+1)
  print =<< getElems a

dice :: IO Int
dice = getStdRandom $ randomR (1, 6)

replica5 :: Monad m => m a -> m [a]
replica5 = replicateM 5

printReplica = do
  print =<< replica5 (return 4)
  print =<< replica5 dice

printReplica' = replicateM_ 3 $ print =<< dice

printWithFor = do
  a <- forM [1 .. 3] $ \x -> do print x
                                return x
  print a

inc x = x + 1

add x y = x + y

main = print =<< (add <$> return 10 <*> return 10 )

-- main = print =<< replicateM' 5 dice

-- when' = do
--   r <- dice
--   print r
--   when (r /= 3) main

-- main = print 5 >> print 7

-- f1 x = putStr

-- f = putStr >=> print
-- f2 = print <=< putStr

-- main = f "4" >> f2 "f"
