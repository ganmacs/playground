import Control.Monad
import System.Random
import Data.List

rand :: IO Double
rand = getStdRandom $ randomR (0.0, 1.0)

randomN = do
  rands <- replicateM 12 rand
  return $ (truncate $ sum rands) - 6

genRandomN n = replicateM n randomN

main = do
  ds <- genRandomN 100
  forM_ [-3..3] $ \i -> do
    let l = length $ filter (== i) ds
        l' = show i
        n = replicate (2 - length l') ' ' ++ l'
    putStrLn $ n ++ ": " ++ replicate l '*'
