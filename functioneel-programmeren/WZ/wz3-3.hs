import Data.Char
-- Oefening 1
upperdare :: [Char] -> [Char]
upperdare = map toUpper

-- Oefening 2
selecteer :: [Char] -> [Char]
selecteer = filter isUpper

-- Oefening 3
klinkers :: [Char] -> [Char]
klinkers = map (\x -> if x `elem` "aeiou" then toUpper x else x)

-- Oefening 4
sumOfSquares :: Int -> Int
sumOfSquares n = sum . map (^2) . digits $ n
  where
    digits = map (read . (:[])) . show

-- Functie die bepaalt of een getal gelukkig is
isHappy :: Int -> Bool
isHappy n = isHappyHelper n []

isHappyHelper :: Int -> [Int] -> Bool
isHappyHelper 1 _ = True
isHappyHelper n visited
  | n `elem` visited = False
  | otherwise = isHappyHelper (sumOfSquares n) (n : visited)

happyNumbers :: [Int]
happyNumbers = filter isHappy [1..200]

-- Oefening 5
isPriem :: Integral a => a -> Bool
isPriem 1 = False
isPriem n = null [x | x <- [2..(n-1)], n `mod` x == 0]

priems :: Integral a => [a] -> [a]
priems xs = [x | x <- xs, isPriem x]

-- Oefening 6
twee :: Num b => b -> b -> b -> [b] -> [b]
twee a b c = map (\x -> a*x*x + b*x + c)