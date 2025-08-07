module Main (main) where
    
import qualified Data.Set as Set
import MaxBipartiteMatching (matching)

edges :: Set.Set (Char, Char)
edges = Set.fromList
  [ ('k', 'c'), ('k', 'd'), ('k', 'e')
  , ('c', 'a'), ('c', 'd'), ('c', 'f')
  , ('l', 'b'), ('l', 'e'), ('l', 'f')
  , ('q', 'a'), ('q', 'b'), ('q', 'c'), ('q', 'e')
  , ('m', 'd'), ('m', 'f'), ('m', 'g')
  , ('n', 'a'), ('n', 'g'), ('n', 'h')
  ]

main :: IO ()
main = do
    let filteredEdges = Set.filter (\(x,y) -> x /= y) edges
    let result = matching filteredEdges
    print result
    let l = length result
    print l
