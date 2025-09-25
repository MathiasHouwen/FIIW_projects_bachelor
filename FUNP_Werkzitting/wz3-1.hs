-- Oefening 1
kwadraatsom :: (Num a, Enum a, Ord a) => a -> a
kwadraatsom n = sum [x*x | x <- [1..n], x*x < n]

-- Oefening 2
perfectNumbers :: Integral a => a -> [a]
perfectNumbers limit = [n | n <- [1..limit], isperfect n]

isperfect :: Integral a => a -> Bool
isperfect n = sum delers == 2 * n
    where delers = [x | x <- [1..n], n `mod` x == 0]

-- Oefening 3
uniek :: Eq a => [a] -> [a] -> [a]
uniek xs ys = [x | x <- xs, x `notElem` ys] ++ [y |y <- ys, y `notElem` xs]