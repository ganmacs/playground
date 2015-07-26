divide x 0 = error "errora"
divide x y = (x/y)

divideMay x 0 = Nothing
divideMay x y = Just (x/y)


divide' :: Double -> Double -> Either String Double
divide' x 0 = Left "error"
divide' x y = Right (x/y)

main = print $ do
  a <- divide' 10 0
  return $ a * 10
