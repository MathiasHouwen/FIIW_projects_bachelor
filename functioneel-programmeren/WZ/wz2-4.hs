-- Oefening 1


-- Oefening 2
nulpunten :: (Ord a, Floating a) => a -> a -> a -> (a, a)
nulpunten a b c
    | d < 0 = error "Geen nulpunten"
    | d == 0 = (x, x)
    | d > 0 = (x, y)
    where 
        d = b * b - 4 * a * c
        x = (-b + sqrt d) / (2 * a)
        y = (-b - sqrt d) / (2 * a)

-- Oefening 3
voorkomers :: (Num b, Eq t) => [t] -> [(t, b)]
voorkomers [] = []
voorkomers (x:xs) =
    let andere = voorkomers xs
        voegToe x [] = [(x,1)]
        voegToe x ((y,n):vs) = if x==y then (x,n+1):vs else (y,n) : voegToe x vs
    in voegToe x andere

-- Oefening 4
