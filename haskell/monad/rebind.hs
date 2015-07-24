{-# LANGUAGE UnboxedTuples #-}

import Data.STRef
import GHC.ST

unST (ST x) = x

return' x = ST $ \s -> (# s, x #)

a `bind` f = ST $ \s ->
  let (# s1, v1 #) = unST a s
      (# s2, v2 #) = unST (f v1) s1
  in (# s2, v2 #)

main = do
  print $ runST $
    return' 1 `bind` newSTRef `bind` \a ->
    modifySTRef a (+1) `bind` \_ ->
    readSTRef a `bind` return'
