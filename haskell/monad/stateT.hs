import Control.Monad.State

-- newtype StateT s m a = StateT { runStateT :: s -> m (a, s) }

-- main = print $ runStateT ((get :: StateT Int [] Int) >>= \_ -> return 10) 0
-- main = runStateT ((get :: StateT [Int] IO [Int]) >>= \a -> lift(print a) >> put (10:a)) [1,2,3]

-- main = print $ runStateT ((get :: StateT Int [] Int) >>= \x -> modify (+1) >>= \_ -> put 1 >>= \_ -> return x) 0

-- instance Monad m => StateT (StateT s m) where
--   return x = StateT $ \s -> return (x, s)
--   m >>= k = StateT $ \s -> do
--     (a, s') <- runStateT m s
--     runStateT (k a) s'

type Stack a = [a]

type StateE s a = StateT s Maybe a

pop :: StateE (Stack Int) Int
pop = do
  (x:xs) <- get
  put xs
  return x

push :: Int -> StateE (Stack Int) ()
push i = do
  xs <- get
  put $ i:xs

stackTest :: StateE (Stack Int) ()
stackTest = do
  a <- pop
  b <- pop
  -- a <- lift(Just a >>= \s -> Just $ s + 1)
  push (a + b)

main :: IO ()
main = print $ runStateT stackTest [1, 2]
