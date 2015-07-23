{-# LANGUAGE UnboxedTuples, MagicHash #-}

import GHC.Base

a `bind` f = IO $ \s ->
  let (# s1, v #) = unIO a s
      (# s2, v2 #) = unIO (f v) s1
  in (# s2, v2 #)


return' v = IO $ \s ->  (# s, v #)

main = return' "adsff" `bind` putStr `bind` print
