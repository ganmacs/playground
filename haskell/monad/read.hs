import Control.Monad.State
import Control.Monad.Reader

localBind = (`runReader` 1) $ do
  a <- ask
  b <- local (+1) $ do
    b' <- ask
    return b'
  c <- ask
  return (a, b, c)

a `bind` f = reader $ \r ->
    runReader (f $ runReader a r) r

ask' = reader $ \x -> x

return' x = reader $ \_ -> x

local' f m = reader $ \r -> runReader m $ f r

test x = (`runReader` x) $
         ask' `bind` \a ->
         (local' (+ 1) $
          ask' `bind` \b' ->
          return' b') `bind` \b ->
         ask' `bind` \c ->
         return' (a, b, c)

test1 x = (`runReader` x) $ do
  a <- ask
  b <- local (+ 1) $ do
    b' <- ask
    return b'
  c <- ask
  return (a, b, c)

main = print $ test1 1

-- main = print $ runReader (ask' `bind` (\x -> return $ x + 1)) 0

-- main = print $ localBind
  -- let a = reader $ \_ -> 1
  -- print $ runReader a ()

  -- print $ (`runState` 1) $ do
  --   a <- get
  --   return $ a + 1
  -- print $ (`runReader` 1) $ do
  --   a <- ask
  --   return $ a + 1
