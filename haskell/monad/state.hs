import Control.Monad.State

a :: State s Int
a = return 1

-- test1 :: State s Int
-- test1 = do
--   a <- get
--   put $ a + 1
--   modify (* 2)
--   return a


sum' xs = (`execState` 0) $ do
  forM_ xs $ \i ->
    modify (i+)

-- main = print $ runState test1 5
-- main = print $ sum' [1 .. 10]

-- main = do
--   let a = return 1 :: State s Int
--   print $ runState a ()

return' a = state $ \s -> (a, s)
v `bind` f = state $ \s ->
  let (v1, s1) = runState v s
      (v2, s2) = runState (f v1) s1
  in (v2, s2)

put' v = state $ \_ -> ((), v)
get' = state $ \s -> (s, s)

fib x = (`evalState` (0, 1)) $
        (replicateM_ (x - 1) $
         get' `bind` \(a, b) -> put' (b, a + b)) `bind` \_ ->
        get' `bind` \v -> return' $ snd v

fib' x = (`evalState` (0, 1)) $ do
  replicateM_ x $ do
       (a, b) <- get
       put $ (b , a + b)
  v <- get
  return $ snd v

-- main = print $ (`runState` 10) $ return =<< get

main = print $ fib' 10

-- main =  sum' [1..10]

-- main :: IO ()
-- main = do
--   replicateM_ 10 $ print =<< return 1


   -- print $ fib 10

-- test2 = do
--   x <- return :: (Int -> Maybe Int)
--   return x

-- main = case  test2 10 of
--   Just x -> print x
--   Nothing -> print "lll"
