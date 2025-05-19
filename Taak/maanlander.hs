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

-- ============================================== --
-- =============== SIM FUNC ===================== --
-- ============================================== --

-- Simulatiefunctie
simuleerLanding :: Strategie -> Maanlander -> IO ()
simuleerLanding strategie maanlander = simuleerHelper strategie [maanlander] 0

-- Hulpfunctie: recursieve simulatie per seconde
simuleerHelper :: Strategie -> [Maanlander] -> Int -> IO ()
simuleerHelper strategie geschiedenis tijd = do
  let huidig = head geschiedenis
  let gas = strategie geschiedenis
  let gasInteger = toInteger gas

  -- Bereken nieuwe waarden
  let versnelling = zwaartekracht huidig - gasInteger
  let nieuweSnelheid = snelheid huidig + versnelling
  let nieuweHoogte = hoogte huidig - nieuweSnelheid
  let nieuweBrandstof = max 0 (brandstof huidig - gasInteger)

  -- Nieuwe toestand
  let nieuw = Maanlander
        { hoogte = max 0 nieuweHoogte
        , snelheid = nieuweSnelheid
        , brandstof = nieuweBrandstof
        , motorkracht = motorkracht huidig
        , maxSnelheid = maxSnelheid huidig
        , zwaartekracht = zwaartekracht huidig
        }

  -- Toon status
  putStrLn ("Tijd: " ++ show tijd ++ "s | Hoogte: " ++ show (hoogte nieuw)
    ++ " m | Snelheid: " ++ show (snelheid nieuw) ++ " m/s | Brandstof: "
    ++ show (brandstof nieuw) ++ " | Tegengas: " ++ show gas)

  -- Check voor landing
  if hoogte nieuw <= 0
    then
      if snelheid nieuw <= maxSnelheid nieuw
        then putStrLn "\n GELAND! Zachte landing."
        else putStrLn "\n CRASH! Te snel geraakt."
    else
      simuleerHelper strategie (nieuw : geschiedenis) (tijd + 1)

-- Beginwaarde voor de maanlander
startMaanlander :: Maanlander
startMaanlander = Maanlander
  { hoogte = 500
  , snelheid = 0
  , brandstof = 120
  , motorkracht = 5
  , maxSnelheid = 5
  , zwaartekracht = 2
  }

-- Main om te testen
main :: IO ()
main = simuleerLanding strategieConstanteRemming startMaanlander