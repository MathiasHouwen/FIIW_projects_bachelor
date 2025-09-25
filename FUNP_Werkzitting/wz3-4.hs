import Data.List
-- Oefening 1
peer :: (Foldable t, Num b) => t b -> b
peer = foldr (*) 1

-- Oefening 2
deel :: Fractional a => [a] -> a
deel [] = 0
deel (x:xs)= foldl (/) x xs

-- Oefening 3
doorsnede :: Eq a => [[a]] -> [a]
doorsnede (x:xs) = foldl intersect x xs

-- Oefening 4
delers :: Int -> [Int]
delers n = [d | d <- [2..n-1], n `mod` d == 0]

isGroterDanSomDelers :: Int -> Bool
isGroterDanSomDelers n = n > sum (delers n)