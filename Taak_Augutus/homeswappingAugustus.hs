import qualified Data.Set as Set
import Data.Graph.MaxBipartiteMatching (matching)
import qualified Data.Map as Map


type Woning = String
type Compat = [(Woning, [Woning])]


-- PARSE INPUT
-- A V C -> ("A",["B","C"])
-- Bronvermelding: https://www.reddit.com/r/haskell/comments/8blpy6/how_to_read_line_by_line_in_haskell/
parseInput :: String -> Compat
parseInput content = map parseLine (lines content)
    where 
        parseLine line = 
            let (woning:verhijzingen) = words line 
            in (woning, verhijzingen)

toEdges :: Compat -> Set.Set (Woning, Woning)
toEdges xs = Set.fromList [ (w, v) | (w, vs) <- xs, v <- vs ]





main :: IO ()
main = do
  content <- readFile "gegenereerd.txt"
  print (parseInput content)