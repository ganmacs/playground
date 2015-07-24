import Control.Monad.Writer

-- main = do
--   print $ (`runState` "") $ do
--     modify (++ "a")
--     modify (++ "b")
--     modify (++ "c")
--     return ()
--   print $ runWriter $ do
--     tell "a"
--     tell "b"
--     tell "c"
--     return "a"

fact ::  Int -> Writer [String] Int
fact 0 = do
  tell ["fact 0 = 1"]
  return 1

fact n
  | n > 0 = do
      let dbg = "fact " ++ show n ++ " = " ++ show n ++ " * fact " ++ show (n-1)
      tell [dbg]
      n' <- fact (n-1)
      let ret = n * n'
      tell [dbg ++ " = " ++ show n ++ " * " ++ show n' ++ " = " ++ show ret]
      return ret

fact' 0 = do
  putStrLn "fact 0 = 1"
  return 1

fact' n
  | n > 0 = do
      let dbg = "fact " ++ show n ++ " = " ++ show n ++ " * fact " ++ show (n-1)
      putStrLn dbg
      n' <- fact' (n-1)
      let ret = n * n'
      putStrLn $ dbg ++ " = " ++ show n ++ " * " ++ show n' ++ " = " ++ show ret
      return ret

-- main = print $ (+1) <$> Just 1
-- main = print $ Just 1 >>= (\x -> Just $ x + 1)

test x = let b = (+1) x
             c = (*2) x
         in (b, c)

main = do
  print $ test 5

-- main = print =<< fact' 10

-- main = do
--   let (a, v) = runWriter $ fact 5
--   print $ unlines v
--   print a

-- tell' = writer \x ->
-- return' :: Int -> Writer [String] Int
-- return' x = writer (x, [])

-- test2 = execWriter $
--         tell' "hello" `bind \_ ->
--         tell' ","     `bind \_ ->
--         tell' "world" `bind \_ ->
--         tell' "!!"    `bind \_ ->
--         return' ()

-- main = print test

-- main = print $ runWriter $ return' 10

-- main = print $ runWriter $ do
--   tell "hello"
--   tell "world"
--   return ()
