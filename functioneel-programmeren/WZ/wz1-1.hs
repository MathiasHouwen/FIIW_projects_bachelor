-- run in console
-- ghci .\wz1-1.hs
-- :r

-- Oefening 1
halveer :: [a] -> [a]
halveer [] = []
halveer (x:_:xs) = x : halveer xs
halveer [x] = [x]

-- Oefening 2
verdubbel :: [a] -> [a]
verdubbel [] = []
verdubbel (x:xs) = x : x : verdubbel xs

-- Oefening 3
isInList elem [] = False
isInList elem (x:xs) = (elem == x) || isInList elem xs

ontdubbel :: Eq a => [a] -> [a]
ontdubbel [] = []
ontdubbel (x:xs) = if isInList x xs then ontdubbel xs else x:ontdubbel xs

-- Oefening 4
f4 :: Num a => [a] -> [a] -> a
f4 [] [] = 0
f4 (x:xs) (y:ys) = (x*y) + f4 xs ys

-- Oefening 5
somList :: Num a => [a] -> a
somList [] = 0
somList (x:xs) = x + somList xs

ontlijst :: Num a => [[a]] -> [a]
ontlijst [] = [];
ontlijst(x:xs) = somList x : ontlijst xs