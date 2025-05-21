import Data.Char (toLower)
import Data.List (nub)
import qualified Data.Set as Set

-- Type klasse
class Similarity a where
    similarity :: a -> a -> Double  -- tussen 0 en 1
    distance :: a -> a -> Double    -- afstand (pseudo-metriek)

-- Gemeenschappelijk klinkers helpers
vowels :: [Char]
vowels = "aeiou"

commonVowels :: String -> String -> Int
commonVowels s1 s2 = length $ nub $ filter (`elem` s2Vowels) s1Vowels
  where
    s1Vowels = filter (`elem` vowels) (map toLower s1)
    s2Vowels = filter (`elem` vowels) (map toLower s2)

totalVowels :: String -> String -> Int
totalVowels s1 s2 = length $ nub (s1Vowels ++ s2Vowels)
  where
    s1Vowels = filter (`elem` vowels) (map toLower s1)
    s2Vowels = filter (`elem` vowels) (map toLower s2)

instance Similarity String where
    similarity s1 s2
        | total == 0 = 0
        | otherwise = fromIntegral common / fromIntegral total
      where
        common = commonVowels s1 s2
        total = totalVowels s1 s2

    distance s1 s2 = 1 - similarity s1 s2

instance Similarity Int where
    similarity x y = 1 - (absDist / maxDist)
      where
        absDist = fromIntegral (abs (x - y))
        maxDist = 100
    
    distance x y = fromIntegral (abs (x - y))

data Point = Point Double Double deriving (Show, Eq)
instance Similarity Point where
    similarity (Point x1 y1) (Point x2 y2) = 1 - (d / maxD)
      where
        d = sqrt ((x2 - x1)^2 + (y2 - y1)^2)
        maxD = 100

    distance (Point x1 y1) (Point x2 y2) = sqrt ((x2 - x1)^2 + (y2 - y1)^2)

-- Verieste functies
filterBySimilarity :: (Similarity a) => [a] -> Double -> a -> [a]
filterBySimilarity xs threshold ref = filter (\x -> similarity x ref >= threshold) xs

triangleInequalityRespected :: (Similarity a) => [a] -> Bool
triangleInequalityRespected xs = all checkTriplets [(x,y,z) | x <- xs, y <- xs, z <- xs]
  where
    checkTriplets (a, b, c) = distance a b + distance b c >= distance a c

reachable :: (Similarity a, Eq a, Ord a) => [a] -> a -> a -> Double -> Bool
reachable xs start end minSim = go Set.empty [start]
  where
    go _ [] = False
    go visited (x:queue)
        | x == end = True
        | otherwise = go newVisited (queue ++ neighbors)
      where
        newVisited = Set.insert x visited
        neighbors = [y | y <- xs, not (Set.member y visited), similarity x y >= minSim]
