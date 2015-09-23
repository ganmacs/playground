fibNotMemo :: Integer -> Integer
fibNotMemo 0 = 0
fibNotMemo 1 = 1
fibNotMemo i = fibNotMemo(i-1) + fibNotMemo(i-2)


fibLast :: Integer -> Integer
fibLast x = iter x 0 1
  where
    iter :: Integer -> Integer -> Integer -> Integer
    iter 0 a _ =  a
    iter n a b = iter (n-1) b (a + b)




-- data Result = Either String

-- data Parsed s v = StateT s Result v

-- data Drivs = Drivs {
--   num :: Parsed Drivs Integer,
--   c :: Parsed Drivs Char
-- }

-- eval :: String -> Drivs
-- eval s = d where
--   d = Drivs num c
--   num = number d
--   c = case s of
--     [] -> ''
--     (x:xs) ->


-- number :: Drivs -> Parsed Drivs Integer
-- number d = num d

-- main :: IO ()
-- main = print $ eval "1"

-- main = print $ fibNotMemo 33
