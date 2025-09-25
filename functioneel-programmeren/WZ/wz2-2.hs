-- Snelle Machtsfunctie
fastExp :: (Num a, Integral b) => a -> b -> a
fastExp _ 0 = 1
fastExp x n
  | even n    = fastExp (x * x) (n `div` 2)
  | otherwise = x * fastExp x (n - 1)

-- Euclides ggd
ggd :: Integral t => t -> t -> t
ggd x 0 = x
ggd x y = ggd y (x `mod` y)