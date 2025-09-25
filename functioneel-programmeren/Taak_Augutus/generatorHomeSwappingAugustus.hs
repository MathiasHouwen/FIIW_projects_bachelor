module Main (main) where
import Data.List (nub)
import System.Random
import System.Random.Shuffle (shuffleM)

{-
printInts = do
  g <- newStdGen
  let numbers = (randomRs (1, 10) g) :: [Integer]
  let n10 = take 10 numbers
  print n10 

printChars = do
    g <- newStdGen
    let chars = (randomRs ('a', 'z') g)
    let c10 = take 10 chars
    print c10
-}

willekeurigeWoningen :: [a] -> Int -> Int -> IO [a]
willekeurigeWoningen ws minC maxC = do
  aantal <- randomRIO (minC, min maxC (length ws))
  take aantal <$> shuffleM ws

getUniqueChars :: Int -> IO [Char]
getUniqueChars n = do
  g <- newStdGen
  let chars = randomRs ('a', 'z') g
      uniqueChars = nub chars
  return (take n uniqueChars)

genereerLijn :: String -> [String] -> Int -> Int -> IO String
genereerLijn w ws minC maxC = do
  willekeurig <- willekeurigeWoningen ws minC maxC
  return $ w ++ " " ++ unwords willekeurig

genereerBestand :: FilePath -> [String] -> Int -> Int -> IO ()
genereerBestand filePath woningen minC maxC = do
  lijnen <- mapM (\w -> genereerLijn w woningen minC maxC) woningen
  writeFile filePath (unlines lijnen)

main :: IO ()
main = do
  putStrLn "Hoeveel woningen wil je genereren? (bijv. 10):"
  aantal <- readLn

  putStrLn "Geef het minimum aantal connecties per woning:"
  minC <- readLn

  putStrLn "Geef het maximum aantal connecties per woning:"
  maxC <- readLn

  chars <- getUniqueChars aantal
  let woningen = map (:[]) chars

  genereerBestand "gegenereerd.txt" woningen minC maxC
