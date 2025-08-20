import System.IO
import Data.List (nub, permutations, maximumBy)
import Data.Ord (comparing)

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