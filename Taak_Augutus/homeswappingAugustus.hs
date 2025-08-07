import qualified Data.Set as Set
-- Bronvermelding: https://hackage.haskell.org/package/maxBipartiteMatching-0.1.0.0/candidate
import MaxBipartiteMatching (matching)
import qualified Data.Map as Map


type Woning = String
type Compat = [(Woning, [Woning])]


-- (STAP 1) PARSE INPUT
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

filterdEdges :: Eq a => Set.Set (a, a) -> Set.Set (a, a)
filterdEdges edges = Set.filter (\(x, y)-> x /= y) edges


main :: IO ()
main = do
  content <- readFile "gegenereerd.txt"
  let compat = parseInput content
      edges = toEdges compat
      result = matching edges -- (STAP 2) BEPAAL swaps
  putStrLn "Maximum matching:"
  print result
  let aantalMatches = length result -- (STAP 3) TEL SWAPS
  print aantalMatches