-- http://d.hatena.ne.jp/nskj77/20070512/1178952068
-- GHCi, version 7.10.1

import Control.Monad(liftM,ap)

data FB a = FB (a, String)

instance Applicative FB where
  pure = return
  (<*>) = ap

instance Functor FB where
  fmap = liftM

instance Monad FB where
  return x = FB (x, "")
  m >>= f = bind m where
    bind (FB (a, b)) = let FB (yy, y) = f a in FB (yy, b ++ y)

instance (Show a) => Show (FB a) where
  show (FB (x, "")) = show x
  show (FB (_, y)) = y

fizz :: Integral a => a -> FB a
fizz x
  | x `mod` 3 == 0 = FB (x, "fizz")
  | otherwise = return x

buzz :: Integral a => a -> FB a
buzz x
  | x `mod` 5 == 0 = FB (x, "buzz")
  | otherwise = return x

-- monadicFizzBuzz ::  Int -> FB Int
-- monadicFizzBuzz x = fizz x >>= buzz

monadicFizzBuzz ::  Int -> FB Int
monadicFizzBuzz x = do
  y <- fizz x
  buzz y

main :: IO ()
main = print $ monadicFizzBuzz 15
