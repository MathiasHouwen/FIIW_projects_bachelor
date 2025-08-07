import Data.Char (toLower)
import Data.List (nub)
import qualified Data.Set as Set
import GHC.Float (Floating(sqrt))
import GHC.Real (fromIntegral)

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
  similarity p1 p2 = 1 - (distance p1 p2 / maxD)
    where
      maxD = 100

  distance (Point x1 y1) (Point x2 y2) =
    sqrt ((x2 - x1)^2 + (y2 - y1)^2)

data Color = Color Int Int Int deriving (Show, Eq)
instance Similarity Color where
  similarity c1 c2 = 1 - (distance c1 c2 / maxD)
    where
      maxD = sqrt (3 * (255^2))

  distance (Color r1 g1 b1) (Color r2 g2 b2) =
    sqrt (fromIntegral ((r1 - r2)^2 + (g1 - g2)^2 + (b1 - b2)^2))

-- Verieste functies
