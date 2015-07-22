import Control.Monad
import System.Random

dice :: IO Int
dice = getStdRandom $ randomR (1, 6)

replicateM' 0 _ = return []
replicateM' i a | i > 0 = (:) <$> a <*> replicateM' (i-1) a

replicateM_' 0 _ = return ()
replicateM_' i a | i > 0 = a >> replicateM_' (i-1) a

forM' [] _ = return []
forM' (x:xs) a = (:) <$> a x <*> forM' xs a

forM_' [] _ = return ()
forM_' (x:xs) a = a x >> forM_' xs a

when' bool f = if bool then f else return ()

unless' bool = when' (not bool)

main :: IO ()
main = do
  print =<< replicateM' 10 dice
  putStrLn "---"

  replicateM_' 3 $ do
    print =<< dice
  putStrLn "---"

  l <- forM' [1..3] $ \i -> do
    print i
    return i
  print l

  putStrLn "---"
  forM_' [1..3] $ \i -> do
    print i
    return i
  putStrLn "---"

  let y f = f (y f)
  y $ \f -> do
      r <- dice
      print r
      when' (r /= 1) f
  putStrLn "---"

  let y f = f (y f)
  y $ \f -> do
      r <- dice
      print r
      unless' (r == 6) f
  putStrLn "---"
