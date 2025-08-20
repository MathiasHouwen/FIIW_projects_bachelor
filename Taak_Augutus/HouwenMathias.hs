import Data.Char (toLower)
import Data.List (nub)
import GHC.Float (Floating(sqrt))
import GHC.Real (fromIntegral)
import Data.List (nub)
import System.Random
import System.Random.Shuffle (shuffleM)
import System.IO
import Data.List (nub, permutations, maximumBy)
import Data.Ord (comparing)

--------------------------------
-- TAAK 1
--------------------------------
-- Datastructuur voor de maanlander
data Maanlander = Maanlander
  { hoogte        :: Integer       -- in meter
  , snelheid      :: Integer       -- in m/s (positief = neerwaarts)
  , brandstof     :: Integer       -- in liter
  , motorkracht   :: Integer       -- maximale kracht in m/s²
  , maxSnelheid   :: Integer       -- maximale veilige landingssnelheid
  , zwaartekracht :: Integer       -- valversnelling in m/s²
  } deriving (Show)

-- Lijst van maanlanders state's geeft terug hoevel tegen gas moet gegeven worden
type Strategie = [Maanlander] -> Int

-- Strategie 1: Constante remming als hoogte < 100 m
strategieConstanteRemming :: Strategie
strategieConstanteRemming (huidig:_) =
  if hoogte huidig < 100 then
    fromInteger (min (brandstof huidig) (motorkracht huidig))
  else 0

-- Strategie 2: Proportioneel remmen afhankelijk van snelheid
strategieProportioneel :: Strategie
strategieProportioneel (huidig:_) =
  let
    gewensteRemming = snelheid huidig - maxSnelheid huidig
    remkracht = max 0 gewensteRemming
    remkrachtBeperkt = min remkracht (min (motorkracht huidig) (brandstof huidig))
  in fromInteger remkrachtBeperkt

-- Strategie 3: Dynamisch gebaseerd op hoogte en snelheid
strategieDynamisch :: Strategie
strategieDynamisch (huidig:_) =
  let
    h  = hoogte huidig
    v  = snelheid huidig
    mv = maxSnelheid huidig
    bf = brandstof huidig
    mk = motorkracht huidig
    tegengas
      | h > 200    = 0
      | h > 100    = if v > mv then 1 else 0
      | h > 50     = if v > mv then 2 else 0
      | h > 20     = if v > mv then 3 else 0
      | otherwise  = min mk (min bf (v - mv + 1))
  in fromInteger tegengas

-- Strategie 4: Gebaseerd op aangepaste afrem-logica
strategie4 :: Strategie
strategie4 (huidig:_) =
  let
    fmax = motorkracht huidig
    vmax = maxSnelheid huidig
    v    = snelheid huidig
    h    = hoogte huidig
    gVal = zwaartekracht huidig
    bf   = brandstof huidig

    vLimiet = fmax - gVal
    gas
      | v > vLimiet = min fmax (min bf (v - vLimiet + gVal))
      | otherwise   = 0
  in fromInteger gas

-- ============================================== --
-- =============== SIM FUNC ===================== --
-- ============================================== --

-- Simulatiefunctie
simuleerLanding :: Strategie -> Maanlander -> IO ()
simuleerLanding strategie maanlander = simuleerHelper strategie [maanlander] 0

-- Hulpfunctie: recursieve simulatie per seconde
simuleerHelper :: Strategie -> [Maanlander] -> Int -> IO ()
simuleerHelper strategie geschiedenis tijd = do
  let huidig = head geschiedenis
  let gas = strategie geschiedenis
  let gasInteger = toInteger gas

  -- Bereken nieuwe waarden
  let versnelling = zwaartekracht huidig - gasInteger
  let nieuweSnelheid = snelheid huidig + versnelling
  let nieuweHoogte = hoogte huidig - nieuweSnelheid
  let nieuweBrandstof = max 0 (brandstof huidig - gasInteger)

  -- Nieuwe toestand
  let nieuw = Maanlander
        { hoogte = max 0 nieuweHoogte
        , snelheid = nieuweSnelheid
        , brandstof = nieuweBrandstof
        , motorkracht = motorkracht huidig
        , maxSnelheid = maxSnelheid huidig
        , zwaartekracht = zwaartekracht huidig
        }

  -- Toon status
  putStrLn ("Tijd: " ++ show tijd ++ "s | Hoogte: " ++ show (hoogte nieuw)
    ++ " m | Snelheid: " ++ show (snelheid nieuw) ++ " m/s | Brandstof: "
    ++ show (brandstof nieuw) ++ " | Tegengas: " ++ show gas)

  -- Check voor landing
  if hoogte nieuw <= 0
    then
      if snelheid nieuw <= maxSnelheid nieuw
        then putStrLn "\n GELAND! Zachte landing."
        else putStrLn "\n CRASH! Te snel geraakt."
    else
      simuleerHelper strategie (nieuw : geschiedenis) (tijd + 1)

-- Beginwaarde voor de maanlander
startMaanlander :: Maanlander
startMaanlander = Maanlander
  { hoogte = 500
  , snelheid = 0
  , brandstof = 500
  , motorkracht = 5
  , maxSnelheid = 5
  , zwaartekracht = 2
  }

-- Main om te testen
main :: IO ()
main = simuleerLanding strategie4 startMaanlander
--------------------------------
-- TAAK 2
--------------------------------

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
similarityList :: (Similarity a) => [a] -> Double -> a -> [a]
similarityList xs threshold refrence = filter (\x -> similarity x refrence >= threshold) xs

checkTriangleInequality :: (Similarity a, Eq a) => [a] -> Bool
checkTriangleInequality xs = all driehoeksongelijkheids [(x, y, z) | x <- xs, y <- xs, x /= y, z <- xs, x /= z, y /= z]
  where
    driehoeksongelijkheids (a, b, c) = distance a b + distance b c >= distance a c

reachableWithinSimilarityStep :: (Similarity a, Eq a) => [a] -> a -> a -> Double -> Bool
reachableWithinSimilarityStep lijst start end maxStep = 
  zoekPad lijst start end maxStep []

zoekPad :: (Similarity a, Eq a) => [a] -> a -> a -> Double -> [a] -> Bool
zoekPad lijst huidig doel maxStep visited
  | huidig == doel        = True
  | huidig `elem` visited = False
  | otherwise             = any (\neighbour -> 
                                  zoekPad lijst neighbour doel maxStep (huidig : visited)
                                ) validNeighbours
  where
    validNeighbours = [ x
                      | x <- lijst
                      , x /= huidig
                      , similarity huidig x > 1 - maxStep
                      ]
--------------------------------
-- TAAK 3: generator
--------------------------------
{-
printInts = do
  g <- newStdGen
  let numbers = (randomRs (1, 10) g) :: [Integer]
  let n10 = take 10 numbers
  print n10 

printChars = do
    g <- newStdGen
    let chars = (randomRs ('a', 'z') g)
    let c10 = take 10 chars
    print c10
-}

willekeurigeWoningen :: [a] -> Int -> Int -> IO [a]
willekeurigeWoningen ws minC maxC = do
  aantal <- randomRIO (minC, min maxC (length ws))
  take aantal <$> shuffleM ws

getUniqueChars :: Int -> IO [Char]
getUniqueChars n = do
  g <- newStdGen
  let chars = randomRs ('a', 'z') g
      uniqueChars = nub chars
  return (take n uniqueChars)

genereerLijn :: String -> [String] -> Int -> Int -> IO String
genereerLijn w ws minC maxC = do
  willekeurig <- willekeurigeWoningen ws minC maxC
  return $ w ++ " " ++ unwords willekeurig

genereerBestand :: FilePath -> [String] -> Int -> Int -> IO ()
genereerBestand filePath woningen minC maxC = do
  lijnen <- mapM (\w -> genereerLijn w woningen minC maxC) woningen
  writeFile filePath (unlines lijnen)

main :: IO ()
main = do
  putStrLn "Hoeveel woningen wil je genereren? (bijv. 10):"
  aantal <- readLn

  putStrLn "Geef het minimum aantal connecties per woning:"
  minC <- readLn

  putStrLn "Geef het maximum aantal connecties per woning:"
  maxC <- readLn

  chars <- getUniqueChars aantal
  let woningen = map (:[]) chars

  genereerBestand "gegenereerd.txt" woningen minC maxC

--------------------------------
-- TAAK 3: homeswapping
--------------------------------

data Woning = Woning { eigenaar :: String, compatibel :: [String] } deriving (Eq, Show)
data Verhuizing = Verhuizing { van :: String, naar :: String } deriving (Eq, Show)

-- (STAP 1) PARSE INPUT
-- Bronvermelding: https://www.reddit.com/r/haskell/comments/8blpy6/how_to_read_line_by_line_in_haskell/
parseInput :: String -> [Woning]
parseInput content = map parseLine (lines content)
  where
    parseLine line =
      let (woning:verhijzingen) = words line 
      in Woning { eigenaar = woning, compatibel = verhijzingen }

maximaleVerhuizingen :: [Woning] -> [Verhuizing]
maximaleVerhuizingen woningen =
  let eigenaars = map eigenaar woningen
      plannen   = permutations eigenaars
      geldige   = [maakVerhuizingen woningen p | p <- plannen, isGeldigPlan woningen p]
  in maximumBy (comparing length) geldige

isGeldigPlan :: [Woning] -> [String] -> Bool
isGeldigPlan woningen toewijzing =
  and [ toewijzing !! i `elem` compatibel w | (i, w) <- zip [0..] woningen ]
 
maakVerhuizingen :: [Woning] -> [String] -> [Verhuizing]
maakVerhuizingen woningen toewijzing =
  [ Verhuizing (eigenaar w) t | (w, t) <- zip woningen toewijzing, eigenaar w /= t ]

printVerhuizingen :: [Verhuizing] -> IO ()
printVerhuizingen verhuizingen = do
  putStrLn $ "Max aantal echte verhuizingen: " ++ show (length verhuizingen)
  mapM_ (\(Verhuizing v n) -> putStrLn $ "- " ++ v ++ " -> " ++ n) verhuizingen

main :: IO ()
main = do
  content <- readFile "gegenereerd.txt"
  let woningen = parseInput content
  let maxSet   = maximaleVerhuizingen woningen
  printVerhuizingen maxSet