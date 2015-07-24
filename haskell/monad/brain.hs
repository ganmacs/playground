{-# LANGUAGE UnboxedTuples #-}

import GHC.Base
import GHC.ST
import Control.Monad
import Control.Monad.ST
import Data.IORef
import Data.STRef
import Data.Array.ST

str = "+++++++++[>++++++++<-]>."

len' = length str - 1

main = do
  let jump = runST $ do
        jmp <- newArray (0, len') 0 ::  ST s (STUArray s Int Int)
        loop' <- newSTRef []
        forM_ [0 .. len'] $ \i ->
          case str !! i of
          '[' -> modifySTRef loop' (i:)
          ']' -> do
            start <- do
              (x:xs) <- readSTRef loop'
              writeSTRef loop' xs
              return x
            writeArray jmp start i
            writeArray jmp i start
          _ -> return ()
        getElems jmp
  print jump
