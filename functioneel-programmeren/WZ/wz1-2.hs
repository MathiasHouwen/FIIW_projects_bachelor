-- Oefening 1
hermit 1 = 1
hermit n = (1/n) + hermit (n-1)

-- Oefening 2
mysterie n = if (mod n 2) == 0 then (div n 2) else (3*n +1)

-- Oefening 3
aantalDelersHulp :: (Integral t, Num a) => t -> t -> a
aantalDelersHulp target 0 = 0;
aantalDelersHulp target n = if (mod target n) == 0 then 1 + aantalDelersHulp target (n-1) else aantalDelersHulp target (n-1)

aantalDelers :: (Integral t, Num a) => t -> a
aantalDelers 0 = 0;
aantalDelers n = aantalDelersHulp n n

-- Oefening 4
isPriem :: Integral t => t -> Bool
isPriem n = aantalDelers n == 2

-- Oefening 5
