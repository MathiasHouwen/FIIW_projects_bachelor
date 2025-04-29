import Data.List (group, sort, maximumBy)
import Data.Ord (comparing)

meestVoorkomend :: (Ord a) => [a] -> a
meestVoorkomend xs = head $ maximumBy (comparing length) $ group $ sort xs
