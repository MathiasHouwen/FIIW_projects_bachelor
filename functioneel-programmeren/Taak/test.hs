import qualified Data.Set as Set
import Data.Graph.MaxBipartiteMatching (matching)

edges :: Set.Set (Char, Char)
edges = Set.fromList 
    [ ('k','k'), ('k','c')
    , ('c','c'), ('c','k')
    , ('l','l'), ('l','k')
    , ('q','q'), ('q','k'), ('q','c')
    ]