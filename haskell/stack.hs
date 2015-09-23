import Control.Monad.State

type Stack s = StateT [s] Maybe s

push :: Integer -> Stack Integer
push i = do
  a <- get
  put $ i:a
  return i

unshift :: Integer -> Stack Integer
unshift i = do
  a <- get
  put $ append i a
  return i
  where append :: Integer -> [Integer] -> [Integer]
        append ii = foldr (:) [ii]

shift = pop

pop :: Stack Integer
pop = do
  (x:xs) <- get
  put xs
  return x

adder :: Stack Integer
adder = do
  a <- pop
  b <- pop
  return $ a + b

-- main = print $ runStateT (unshift 1 >> shift >> pop >> push 10) [32, 3]

hoge :: Maybe Integer -> Maybe Integer
hoge b = do
  a <- b
  return $ a + 1

main = print $ hoge (Just 10)
