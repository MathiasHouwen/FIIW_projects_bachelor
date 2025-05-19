-- Datastructuur voor de maanlander
data Maanlander = Maanlander
  { hoogte        :: Integer       -- in meter
  , snelheid      :: Integer       -- in m/s (positief = neerwaarts)
  , brandstof     :: Integer       -- in liter
  , motorkracht   :: Integer       -- maximale kracht in m/s²
  , maxSnelheid   :: Integer       -- maximale veilige landingssnelheid
  , zwaartekracht :: Integer       -- valversnelling in m/s²
  } deriving (Show)

-- Lijst van maanlanders state's geeft terug hoevel tegen gas moet gegeven worden
type Strategie = [Maanlander] -> Int

-- Strategie 1: Constante remming als hoogte < 100 m
strategieConstanteRemming :: Strategie
strategieConstanteRemming (huidig:_) =
  if hoogte huidig < 100 then
    fromInteger (min (brandstof huidig) (motorkracht huidig))
  else 0

-- Strategie 2: Proportioneel remmen afhankelijk van snelheid
strategieProportioneel :: Strategie
strategieProportioneel (huidig:_) =
  let
    gewensteRemming = snelheid huidig - maxSnelheid huidig
    remkracht = max 0 gewensteRemming
    remkrachtBeperkt = min remkracht (min (motorkracht huidig) (brandstof huidig))
  in fromInteger remkrachtBeperkt

-- Strategie 3: Dynamisch gebaseerd op hoogte en snelheid
strategieDynamisch :: Strategie
strategieDynamisch (huidig:_) =
  let
    h  = hoogte huidig
    v  = snelheid huidig
    mv = maxSnelheid huidig
    bf = brandstof huidig
    mk = motorkracht huidig
    tegengas
      | h > 200    = 0
      | h > 100    = if v > mv then 1 else 0
      | h > 50     = if v > mv then 2 else 0
      | h > 20     = if v > mv then 3 else 0
      | otherwise  = min mk (min bf (v - mv + 1))
  in fromInteger tegengas
