import Control.Monad.State

type Stack = State [Int] Int

push :: Int -> Stack
push i = do
  xs <- get
  put $ i:xs
  return i

pop :: Stack
pop = do
  cs <- get
  put (tail cs)
  return (head cs)


calc :: (Int -> Int -> Int) -> Stack
calc op = do
  v1 <- pop
  v2 <- pop
  push (op v1 v2)

add = calc (+)
sub = calc (-)

-- main = print $ runState (push 3 >>= \_ -> pop) [11]
main = print $ runState sub [11, 19]
