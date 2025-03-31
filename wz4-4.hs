tweeMaal [] = []
tweeMaal (x:xs) = x:x:(tweeMaal xs)

tweeMaalSpecifiek [] = []
tweeMaalSpecifiek xs = tweeMaal' xs []

tweeMaal' :: [Int] -> [Int] -> [Int]
tweeMaal' [] xs = reverse xs
tweeMaal' (x:xs) ys = tweeMaal' xs (x:x:ys)

data Temperatuur = Warm | Normaal | Koud
data Seizoen = Lente | Zomer | Herfst | Winter

weer Zomer = Warm
weer Winter = Koud
weer _ = Normaal


data Geslacht = M | V | X deriving (Show, Eq, Ord)
data Mens = Mens String Integer Geslacht deriving (Show, Eq, Ord)

data Punt = Punt {
                x :: Float,
                y :: Float
            }                deriving (Show, Eq, Ord)

pt1 = Punt 3 4

afstand (Punt x1 y1) (Punt x2 y2) = sqrt(dx*dx + dy*dy)
   where dx = x1 - x2
         dy = y1 - y2
         
         
type Naam = String
type Leeftijd = Integer

data Mens2 = Mens2 { naam :: Naam, 
                     leeftijd :: Leeftijd,
                     sexe :: Geslacht 
} deriving (Show, Eq, Ord)
                   
maakJan leeftijd = Mens2 "Jan" leeftijd M 

data Point a = Pt a a deriving (Show, Eq, Ord)

afstandPt (Pt x1 y1) (Pt x2 y2) = sqrt (dx * dx + dy * dy)
    where  dx = x2 - x1
           dy = y2 - y1 
           
data SimpleVorm = Cirkel Float | Rechthoek Float Float deriving (Show, Eq, Ord)

isRond (Cirkel _) = True
isRond (Rechthoek _ _) = False

-- Oefening: bereken de oppervlake van een simpele vorm
oppervlakte :: SimpleVorm -> Float
oppervlakte (Cirkel r) = pi * r * r
oppervlakte (Rechthoek w h) = w * h

--- Oefeningen  met examenscores ---

-- 1. Maak een type Examenscore met naam van vak, een punt op 20 en het aantal studiepunten van het vak
data Examenscore = Examenscore {
    vak :: String,
    score :: Integer,
    studiepunten :: Integer
} deriving (Show, Eq, Ord)

-- 2. Maak een functie die een tuple van 3 waarden (string + 2 getallen) omzet in een Examenscore
omzetten :: (String, Integer, Integer) -> Examenscore
omzetten (vak, score, studiepunten) = Examenscore vak score studiepunten

-- 3. Maak een functie die een lijst van tuples omzet in een lijst van Examenscores
omzetlijst :: [(String, Integer, Integer)] -> [Examenscore]
omzetlijst ((vak, score, studiepunten):xs) = omzetten (vak, score, studiepunten) : omzetlijst xs

-- 4. Pas die functies toe om volgende lijsten om te zetten
student1 = [("MP",14,20),("A",9,4),("B",12,6),("C",18,5),("D",11,4),("E",13,4),("F",12,5),("G",12,4),("H",14,4),("I",15,4)] 
student2 = [("MP",14,20),("A",7,4),("B",12,6),("C",18,5),("D",11,4),("E",13,4),("F",12,5),("G",12,4),("H",14,4),("I",15,4)] 
student3 = [("MP",14,20),("A",9,4),("B",9,6),("C",8,5),("D",11,4),("E",13,4),("F",12,5),("G",12,4),("H",14,4),("I",15,4)] 
student4 = [("MP",14,20),("A",17,4),("B",12,6),("C",18,5),("D",16,4),("E",14,4),("F",19,5),("G",12,4),("H",15,4),("I",17,4)] 
student5 = [("MP",11,20),("A",11,4),("B",11,6),("C",11,5),("D",11,4),("E",11,4),("F",11,5),("G",11,4),("H",11,4),("I",11,4)] 


-- 5. Schrijf een functie die het gewogen gemiddelde van examenscores + de graad terug geeft
-- Berekening van de graad:
--      minstens één vak met hoogstens 7/20 => niet-geslaagd 
--      meer dan 10% van de studiepunten een 8 of 9 => niet-geslaagd
--      geslaagd en meer dan 85% => grootste onderscheiding
--      geslaagd en tussen 76% en 85% => grote onderscheiding
--      geslaagd en meer dan 68% => onderscheiding
--      geslaagd en minder dan 68% => voldoening

-- Functie om het gewogen gemiddelde te berekenen
gewogenGemiddelde :: [Examenscore] -> Double
gewogenGemiddelde scores =
    let totaalPunten = sum [fromIntegral (score s) * fromIntegral (studiepunten s) | s <- scores]
        totaalStudiepunten = sum [fromIntegral (studiepunten s) | s <- scores]
    in totaalPunten / totaalStudiepunten

-- Functie om de graad te bepalen
bepaalGraad :: [Examenscore] -> String
bepaalGraad scores
    | any ((<= 7) . score) scores = "Niet-geslaagd"
    | (fromIntegral (sum [sp | Examenscore _ s sp <- scores, s == 8 || s == 9]) / fromIntegral (sum [studiepunten s | s <- scores])) > 0.1 = "Niet-geslaagd"
    | gemiddelde >= 85 = "Grootste onderscheiding"
    | gemiddelde >= 76 = "Grote onderscheiding"
    | gemiddelde > 68 = "Onderscheiding"
    | otherwise = "Voldoening"
  where gemiddelde = gewogenGemiddelde scores

-- Functie die zowel het gewogen gemiddelde als de graad teruggeeft
resultaat :: [Examenscore] -> (Double, String)
resultaat scores = (gewogenGemiddelde scores, bepaalGraad scores)

-- 6. Schrijf een functie die gegeven examenscores de namen van de vakken teruggeeft die hernomen moeten worden
hernemenVakken :: [Examenscore] -> [String]
hernemenVakken scores = [vak s | s <- scores, score s < 10]
    
-- tussendia over Maybe en Either
    
-- 7. Pas de functie van 6 aan zodat Nothing terug gegeven wordt als geen vakken hernomen moeten worden (ipv [])

hernemenVakkena :: [Examenscore] -> Maybe [String]
hernemenVakkena scores =
    let herexamens = [vak s | s <- scores, score s < 10]
    in if null herexamens then Nothing else Just herexamens

-- 8. Combineer de functie 5 en 6 zodat de functie ofwel graad + gewogen gemiddelde terug geeft wanneer de student geslaagd is, 
--    ofwel de lijst met namen van vakken die hernomen moet worden als de student niet geslaagd is

           
data Tree a = Leaf a | Branch a (Tree a) (Tree a)
    deriving (Show, Eq)

boom1 :: Tree String
boom1 = Branch "Kris" (Branch "Louis" (Leaf "Jos") (Leaf "Maria"))
                      (Leaf "Celine")

boom2 :: Tree Int
boom2 = Branch 10 (Branch 6 (Branch 4 (Leaf 1) (Leaf 5))
                            (Branch 15 (Leaf 1) (Branch 17 (Leaf 16) (Leaf 19))))  
                  (Leaf 1)

-- Bereken het aantal knopen van een boom
aantalKnopen :: Tree a -> Int
aantalKnopen (Leaf _) = 1
aantalKnopen (Branch _ left right) = 1 + aantalKnopen left + aantalKnopen right

-- Bereken hoe dikwijls een element voorkomt in de boom
aantalKeer :: Eq a => a -> Tree a -> Int
aantalKeer x (Leaf y) = if x == y then 1 else 0
aantalKeer x (Branch y left right) = (if x == y then 1 else 0) + aantalKeer x left + aantalKeer x right

-- Zoek of een element in een boom zit
bevatElement :: Eq a => a -> Tree a -> Bool
bevatElement x (Leaf y) = x == y
bevatElement x (Branch y left right) = x == y || bevatElement x left || bevatElement x right

-- Zoek het kleinste element in een boom
kleinsteElement :: Ord a => Tree a -> a
kleinsteElement (Leaf x) = x
kleinsteElement (Branch x left right) = minimum [x, kleinsteElement left, kleinsteElement right]

-- Definieer het Boom type
data Boom a b  = Boom (Either a b) 
                | Tak (Either a b) (Boom a b) (Boom a b)
                deriving (Show, Eq, Ord)

-- Implementeer aantalKeren :: a -> b -> Boom a b -> (Int, Int)
aantalKeren :: Eq a => Eq b => a -> b -> Boom a b -> (Int, Int)
aantalKeren x y (Boom (Left a)) = (if x == a then 1 else 0, 0)
aantalKeren x y (Boom (Right b)) = (0, if y == b then 1 else 0)
aantalKeren x y (Tak val left right) = 
    let (lA, lB) = aantalKeren x y left
        (rA, rB) = aantalKeren x y right
        (curA, curB) = case val of
                          Left a -> (if x == a then 1 else 0, 0)
                          Right b -> (0, if y == b then 1 else 0)
    in (curA + lA + rA, curB + lB + rB)
