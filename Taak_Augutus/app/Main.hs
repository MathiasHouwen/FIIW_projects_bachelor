module Main (main) where
    
import qualified Data.Set as Set
import MaxBipartiteMatching (matching)

edges :: Set.Set (Char, Char)
edges = Set.fromList 
    [ ('k','k'), ('k','c')
    , ('c','c'), ('c','k')
    , ('l','l'), ('l','k')
    , ('q','q'), ('q','k'), ('q','c')
    ]

main :: IO ()
main = do
    let filteredEdges = Set.filter (\(x,y) -> x /= y) edges
    let result = matching filteredEdges
    print result
