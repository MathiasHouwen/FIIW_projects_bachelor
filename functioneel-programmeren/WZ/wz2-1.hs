-- oefening 1
{-# OPTIONS_GHC -Wno-overlapping-patterns #-}
afzonder :: Integral a => a -> [a]
afzonder 0 = []
afzonder getal = afzonder (getal `div` 10) ++ [getal `mod` 10]

-- oefening 2
uniek' :: Integral t => t -> [t]
uniek' x = uniek x []

uniek :: Integral t => t -> [t] -> [t]
uniek 0 ys = ys
uniek x ys
    | elem (x `mod` 10) ys = uniek (x `div` 10) ys
    | otherwise = uniek (x `div` 10) ((x `mod` 10) : ys)

-- oefening 3
gemeenschappelijk :: Eq a => [a] -> [a] -> [a]
gemeenschappelijk [] _ = []
gemeenschappelijk _ [] = []
gemeenschappelijk (x:xs) ys
    | x `elem` ys = x : gemeenschappelijk xs (removeFirst x ys)
    | otherwise   = gemeenschappelijk xs ys

removeFirst :: Eq a => a -> [a] -> [a]
removeFirst _ [] = []
removeFirst x (y:ys)
    | x == y    = ys
    | otherwise = y : removeFirst x ys

-- oefening 4
keren :: (Num a1, Eq a2) => [a2] -> [a2] -> a1
keren [] ys = 0;
keren xs [] = 0;
keren [] [] = 0;
keren (x:xs) (y:ys)
    | x == y    = keren xs ys + 1
    | otherwise = keren xs ys