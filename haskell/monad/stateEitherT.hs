import Control.Monad.State
-- import Control.Monad.Except
-- import Control.Monad.Trans.Except
import Control.Monad.Trans.Error ( strMsg )
import Control.Monad.Except

type Fuga = Either String Int

type T s a = StateT s (Either String) a

check :: Int -> Fuga
check x = if x < 10
          then fail "this is fail"
          else return 10

ei :: Int ->  Either String Int
ei x = return =<< check =<< return x

type SAIKOU = State [Int] [Int]

saikou :: SAIKOU
saikou =  do
  a <- get
  put $ 10:a
  c <- get
  put $ 20:c
  b <- get
  modify $ \xs -> fmap (+10) xs
  return b

run :: ([Int], [Int])
run = runState saikou []

-- checkT :: T [Int] Int
-- checkT = do
--   x <- get
--   return =<< lift(che x)
--   where che x = case x of
--           (y:_) -> return y
--           _ -> Left "asdf"

checkT :: T [Int] Int
checkT = che =<< get
  where che x = case x of
          (y:_) -> return y
          _ -> throwError $ strMsg "hoge"


checkT' :: T [Int] Int
checkT' = che =<< get
  where che x = case x of
          (y:_) -> return y
          _ -> lift (Left "Empty")

checkZero :: T Int Int
checkZero = isNotZero =<< get
  where isNotZero x = case x of
          0 -> throwError $ strMsg "NO ZERO!!!!!!!"
          y -> return y

-- main = print $ runStateT checkZero 0
main = print $ runStateT checkT' []


-- main = print $ ei 3
-- main = print run
