import System.Random
import Control.Monad
import Data.List
import qualified Data.Set as Set
import System.Environment

willekeurigeLetters :: Int -> IO [String]
willekeurigeLetters n = do
    g <- newStdGen
    let letters = nub $ take n $ randomRs ('a', 'z') g
    return $ map (:[]) letters

-- Genereer een compatibiliteitslijst voor één woning
genCompat :: [String] -> Int -> Int -> IO [String]
genCompat alle minC maxC = do
    g <- newStdGen
    let k = head $ randomRs (minC, maxC) g
    sub <- fmap (take k . nub . (alle ++)) $ replicateM 10 (elements alle)
    return $ nub sub

elements :: [a] -> IO a
elements xs = do
    g <- newStdGen
    return $ xs !! fst (randomR (0, length xs - 1) g)

-- Genereer volledig compatibiliteitsbestand
genereerBestand :: Int -> Int -> Int -> IO ()
genereerBestand n minC maxC = do
    woningen <- willekeurigeLetters n
    regels <- forM woningen $ \w -> do
        c <- genCompat woningen minC maxC
        return $ unwords (w : (w : filter (/= w) c)) -- Zorg dat woning zichzelf bevat
    writeFile "gegenereerd.txt" (unlines regels)
    putStrLn "Bestand gegenereerd als 'gegenereerd.txt'"

main :: IO ()
main = do
    args <- getArgs
    when (length args < 3) $ error "Gebruik: ./Gen <aantal> <minCompat> <maxCompat>"
    let [n, minC, maxC] = map read args
    genereerBestand n minC maxC
