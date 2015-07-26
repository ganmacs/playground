import Control.Monad
import Control.Monad.State
import Control.Monad.Identity

sum' xs = (`evalState` 0) $ do
  forM_ xs $ \i -> modify (+i)
  get

sumT' xs = (`execStateT` 0) $ do
  forM_ xs $ \i -> do
    modify (+i)
    a <- get
    lift $ putStrLn $ "+" ++ show i ++ " -> " ++ show a
    -- return a


-- main = do
--   let a = return 1 :: Identity Int
--   print $ runIdentity a
-- main = print =<< sumT' [1..10]
