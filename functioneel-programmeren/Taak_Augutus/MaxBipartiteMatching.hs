{-|
Description : Maximum cardinality bipartite matching
Copyright   : © 2012 Stefan Klinger <http://stefan-klinger.de/>
License     : GNU AGPL 3 <http://www.gnu.org/licenses/agpl-3.0.html>
Maintainer  : http://stefan-klinger.de
Stability   : experimental

Find a maximum cardinality matching on a bipartite graph, using an
augmenting path algorithm. More efficient than using MaxFlow from FGL
with constant weight and additional source and sink nodes. But not as
good as Hopcroft–Karp would be.
-}

module MaxBipartiteMatching (matching) where

import qualified Data.Map.Strict as M
import qualified Data.Set as S
import Data.List (foldl')

{-|

A bipartite graph has “left” and “right” nodes, we assume the types α
and β for them. Each edge then is an (α,β) pair, i.e., there are no
edges between nodes on the same side.

A “matching” is a subset of the edges, so that each node is incident to
at most one edge that is in the matching. We are looking for a matching
that contains as many edges as possible. With respect to a fixed
matching, an edge is called “matched” iff it is part of the matching. A
node is called “free” iff it is not incident to any matched edge.

An “augmenting path” contains no cycles, starts at a free α-node,
terminates at a free β-node, and strictly alternately traverses
unmatched and matched edges. Thus, exactly the first and last node of
an augmenting path are free, the inner nodes are not.

The algorithm is based on the idea of repeatedly finding an augmenting path
with respect to a current matching, starting from the empty matching,
similar to Hopcroft–Karp. When an augmenting path is found, all of its
matched edges become unmatched, and vice versa, thus incrementing the
matching's size by one.
-}

{-|
Return a maximum cardinality matching. The input graph is a 'S.Set'
(α,β) of edges, which implies being bipartite and simple. The matching
is returned as an injective 'M.Map' β α, i.e., backwards.

>>> matching $ Data.Set.fromList [(1,'a'),(1,'b'),(2,'a'),(2,'c'),(3,'b')]
fromList [('a',1),('b',3),('c',2)]
-}
matching :: (Ord a, Ord b) => S.Set (a, b) -> M.Map b a
matching g = opt (M.keys fwd, []) fwd M.empty
  where
    -- Build a forward map from each α to list of adjacent βs
    fwd = foldl' (\m (x, y) -> M.insertWith (++) x [y] m) M.empty $ S.toList g

-- Optimization function that grows the matching
opt :: (Ord a, Ord b) => ([a], [a]) -> M.Map a [b] -> M.Map b a -> M.Map b a
opt (x:free, failed) fwd mat =
  either (flip (opt (free, x:failed)) mat) (opt (free ++ failed, []) fwd)
    $ right fwd [] x
  where
    -- Start DFS from a free α-node
    right rem path x =
      maybe (Left rem) (left $ M.delete x rem) $ M.lookup x rem
      where
        left rem [] = Left rem
        left rem (y:ys) =
          maybe
            (Right $ foldr (uncurry $ flip M.insert) mat path') -- A
            (either (flip left ys) Right . right rem path')     -- B
            (M.lookup y mat)                                   -- C
          where
            path' = (x, y) : path

opt ([], failed) _ mat = mat
