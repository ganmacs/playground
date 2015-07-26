import Control.Monad.Trans
import Control.Monad.IO.Class

-- maybe monad を内包したmonad則を満たしたやつ
newtype MaybeT m a = MaybeT { runMaybeT :: m (Maybe a) }

instance Monad m => Functor (MaybeT m) where
  fmap f x = MaybeT $ do a <- runMaybeT x
                         case a of
                           Nothing -> return Nothing
                           Just y  -> return (Just (f y))

instance Monad m => Applicative (MaybeT m) where
  pure x = MaybeT $ pure $ Just x
  (<*>) fa x = MaybeT $ do a <- runMaybeT x
                           case a of
                             Nothing -> return Nothing
                             Just v -> do b <- runMaybeT fa
                                          case b of
                                            Nothing -> return Nothing
                                            Just ff -> return $ Just (ff v)

instance Monad m => Monad (MaybeT m) where
  return x = MaybeT $ return (Just x)
  m >>= k  = MaybeT $ do a <- runMaybeT m
                         case a of
                           Nothing -> return Nothing
                           Just v  -> runMaybeT (k v)
  fail _   = MaybeT $ return Nothing

instance MonadTrans MaybeT where
  lift m = MaybeT $ m >>= \x -> return $ Just x


-- instance (Show a, Monad m) => Show (MaybeT m a) where
--   show m = do a <- runMaybeT m
--               case a of
--                 Nothing -> "Nothing"
--                 Just x -> "Just" ++ show x


-- main = print $ runMaybeT ((return 1 :: MaybeT [] Int) >>= (\x -> return $ x + 1 ))
-- main = print $ runMaybeT $ fmap (*2) (return 1 :: MaybeT [] Int)
-- main = print $ (return 1 :: MaybeT IO Int) >>= liftIO . print
