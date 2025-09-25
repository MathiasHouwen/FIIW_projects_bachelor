-- schaar-steen-papier
data Move = Paper | Rock | Scissors deriving (Eq, Show)
p = Paper
r = Rock
s = Scissors

type Round = (Move, Move)

-- stap 1: score :: Round -> (Int, Int)
score (speler1, speler2) = wieWint speler1 speler2 

wieWint Paper Rock = (1,0)
wieWint Rock Paper = (0,1)
wieWint Rock Scissors = (1,0)
wieWint Scissors Rock = (0,1)
wieWint Paper Scissors = (0,1)
wieWint Scissors Paper = (1,0)
wieWint _ _ = (0,0)


-- stap 2: bereken de score na een reeks rondes
-- scoreNa :: [Round] -> (Int, Int)
scoreNa rs = foldr combineer (0,0) (map score rs)
  where combineer (sp1, sp2) (sc1, sc2) = (sp1 + sc1, sp2 + sc2)


rondes = [(p,p), (r,s), (r,p), (s,p)] 
rondes2 = [(p,p), (r,s), (r,p), (s,p), (s,r), (s,r)] 

-- stap 3: bereken de persoon die het eerste 'n' rondes heeft gewonnen (geeft 1 of 2 terug)
-- bestOf :: Int -> [Round] -> Int 
{-
bestOf_v1 n rs = bestOf2 n rs (0,0)
   where bestOf2 n [] (sp1, sp2) 
            | n == sp1  = 1
            | n == sp2  = 2
            | otherwise = error "niet genoeg rondes"
         bestOf2 n rs (sp1, sp2) 
            | n == sp1  = 1
            | n == sp2  = 2
            | otherwise = let (sc1, sc2) = score (head rs)
                          in bestOf2 n (drop 1 rs) (sp1+sc1, sp2+sc2)
-}

bestOf n rs = bestOf2 n rs (0,0)
   where bestOf2 n [] _ = error "niet genoeg rondes!"
         bestOf2 n (ronde:rs) (sp1, sp2) 
            | n == sp1 + sc1  = 1
            | n == sp2 + sc2  = 2
            | otherwise = bestOf2 n rs (sp1+sc1, sp2+sc2)
            where  (sc1, sc2) = score ronde             

winnaar1 = bestOf 2 rondes
winnaar2 = bestOf 3 rondes2

-- stap 4: 'AI': versla met een slimme strategie je tegenstander 
type Strategy = [Move] -> Move -- lijst in omgekeerde volgorde

-- voorbeelden: altijdSteen, altijd eerste parameter, hetzelfde als de tegenstander vorige keer deed, wint van laatste beurt
altijdSteen _ = Rock

hetZelfde [] = Paper  -- De eerste zet is in principe random, bijvoorbeeld Paper.
hetZelfde (zet:zetten) = zet

wintVan [] = Scissors -- De eerste zet is in principe random, bijvoorbeeld Scissors.
wintVan (Paper:zetten) = Scissors
wintVan (Scissors:zetten) = Rock
wintVan (Rock:zetten) = Paper

-- OEFENING 1
wintMeestal [] = Paper -- terug iets willekeurig
wintMeestal moves = winnaar (telMoves moves) -- kies de zet die wint van de zet die al het meeste gezet is

telMoves [] = (0,0,0)
telMoves (m:ms) =
    let (rock, paper, scissors) = telMoves ms
    in case m of 
          Rock -> (rock+1, paper, scissors)
          Paper -> (rock, paper+1, scissors)
          Scissors -> (rock, paper, scissors+1)

telMovesAcc moves = telMoves moves (0,0,0)
    where telMoves [] tuple = tuple
          telMoves (m:ms) (rock, paper, scissors) 
            = case m of 
                Rock ->     telMoves ms (rock+1, paper, scissors)
                Paper ->    telMoves ms (rock, paper+1, scissors)
                Scissors -> telMoves ms (rock, paper, scissors+1)

winnaar (rock, paper, scissors) =
   let beste = max (max rock paper) scissors
   in if beste == rock then Paper
                       else if beste == paper then Scissors
                                              else Rock

-- NIEUW
-- genereer een oneindige lijst van rondes
-- generateRounds :: (Strategy, Strategy) -> [Round]
generateRounds (speler1, speler2) = nieuweZet [] []
   where nieuweZet moves1 moves2 = let zet1 = speler1 moves2
                                       zet2 = speler2 moves1 
                                   in (zet1, zet2):(nieuweZet (zet1:moves1) (zet2:moves2))

generateNRounds n strategieen = take n (generateRounds strategieen)



type Strategy2 = [Move] -> [Move] -- lijst in omgekeerde

naDrieKeerSchaarSteen _ = [Scissors, Scissors, Scissors] ++ (repeat Rock) 
zelfde xs = Rock:xs
roteer xs = [Rock, Paper, Scissors] ++ (roteer xs)
steenPapier xs = Rock:(papierSteen xs)
papierSteen xs = Paper:(steenPapier xs)
wintVanVorige zetten = Scissors:(map winnaar zetten) -- De eerste zet is in principe random, bijvoorbeeld Scissors.
  where winnaar Rock = Paper
        winnaar Paper = Scissors
        winnaar Scissors = Rock        

generateRoundsStrat2 :: (Strategy2, Strategy2) -> [Round]
generateRoundsStrat2 (p1, p2) =  zip moves1 moves2
    where moves1 = p1 moves2
          moves2 = p2 moves1 
          
generateNRounds2 n strategieen = take n (generateRoundsStrat2 strategieen)
          
-- OEFENING 2
-- wintMeestal2 :: [Move] -> [Move]
wintMeestal2 moves = map winnaar (telMovesList moves)
telMovesList moves = tel moves (0,0,0)
   where tel [] _ = []
         tel (m:ms) (r,p,s) = let nieuweTeller = telOp m (r,p,s)
                              in nieuweTeller:(tel ms nieuweTeller)
         telOp Rock (r,p,s)     = (r+1, p, s)
         telOp Paper (r,p,s)    = (r, p+1, s)
         telOp Scissors (r,p,s) = (r, p, s+1)

          
-- MAAR 
-- wintVanVorige begint met een zet, en pakt dan de winnaar van de vorige zet
-- Dat kan misschien slimmer, want waarom vergelijk je niet direct met de huidige zet?
wintVanVals zetten = map winnaar zetten
  where winnaar Rock = Paper
        winnaar Paper = Scissors
        winnaar Scissors = Rock        

-- uitleg: vals spelen gaat omdat lazy evaluation kijkt naar welke expressie eerst nodig is. 
-- wintVanVals heeft de waarde nodig van de zet van de tegenstander en dwingt dus de tegenstander om eerst de zet te doen.
-- Als je automatischGame (wintVanVals, wintVanVals) probeert, zie je dat beide functies op elkaar wachten. 
-- Twee valsspelers lukt dus niet.

-- Je hebt dus een aanpak nodig die dwingt dat je de eerste zet berekent van speler 1 én speler2 voordat je kijkt wie er wint.
-- Dit kan met de seq-operator.

eerlijkeRondes (speler1, speler2) = zip moves1 moves2 
    where moves1 = fairMoves speler1 moves2
          moves2 = fairMoves speler2 moves1 

fairMoves speler otherMoves = myMoves 
    where myMoves = speler (firstMine otherMoves myMoves)
          firstMine (otherMove:otherMoves) (myMove:myMoves) = (myMove `seq` otherMove):(firstMine otherMoves myMoves)    


headermap f [] = error "ik heb een element nodig"
headermap f (x:xs) = f x

hamming = 1:(mergeOrdered (map (*2) hamming) (map (*3) hamming) (map (*5) hamming))

mergeOrdered (x:xs) (y:ys) (z:zs) = 
   let kleinste = min x (min y z)
       zonder n (m:xs) = if n == m then xs
                                   else m:xs
       xs' = zonder kleinste (x:xs)
       ys' = zonder kleinste (y:ys)
       zs' = zonder kleinste (z:zs)
   in kleinste:(mergeOrdered xs' ys' zs')
         
multiples x = [2*x, 3*x, 5*x]

merge (x:xs) (y:ys)
      | x < y     = x : merge xs (y:ys)
      | x > y     = y : merge (x:xs) ys
      | otherwise = x : merge xs ys
merge xs [] = xs
merge [] ys = ys

hammingSequence :: [Int]
hammingSequence = generate [1]
      where generate (x:xs) = x : generate (merge xs (multiples x))

