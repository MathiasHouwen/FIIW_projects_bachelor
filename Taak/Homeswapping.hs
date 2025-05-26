import System.Environment
import qualified Data.Map as Map
import Data.List
import Data.Maybe
import Control.Monad
import qualified Data.Set as Set

type Woning = String
type Compatibiliteit = Map.Map Woning [Woning]

-- Leest het bestand en bouwt de compatibiliteitsstructuur
leesInvoer :: FilePath -> IO Compatibiliteit
leesInvoer pad = do
    inhoud <- readFile pad
    let lijnen = lines inhoud
    let regels = map (words . filter (/= ',')) lijnen
    return $ Map.fromList [(head r, tail r) | r <- regels]

-- Genereert alle geldige bijecties volgens de compatibiliteitsregels
geldigeBijecties :: Compatibiliteit -> [[(Woning, Woning)]]
geldigeBijecties compat = filter geldigBijectie allePermutaties
  where
    woningen = Map.keys compat
    allePermutaties = map (zip woningen) (permutations woningen)
    geldigBijectie = all (\(van, naar) -> naar `elem` (compat Map.! van))

-- Bereken het maximaal aantal verhuizingen
maxVerhuizingen :: Compatibiliteit -> Int
maxVerhuizingen compat =
    maximum [length $ filter (uncurry (/=)) bijectie | bijectie <- geldigeBijecties compat]

main :: IO ()
main = do
    args <- getArgs
    when (null args) $ error "Gebruik: ./Main <invoerbestand>"
    let pad = head args
    compat <- leesInvoer pad
    let resultaat = maxVerhuizingen compat
    putStrLn $ "Maximaal aantal echte verhuizingen: " ++ show resultaat
