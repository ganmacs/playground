import Control.Monad.Except
import Control.Monad.Trans.Except

type ExceptIO a = ExceptT String IO a

getWord :: ExceptIO String
getWord = do
  lift (putStr "input>")
  a <- lift getLine
  when (a == "") (fail "empty string")
  return a
