data Complex = Complex Double Double
    deriving (Eq, Show)

instance Num Complex where
    -- Optellen
    (+) :: Complex -> Complex -> Complex
    (Complex a b) + (Complex c d) = Complex (a + c) (b + d)

    -- Aftrekken
    (-) :: Complex -> Complex -> Complex
    (Complex a b) - (Complex c d) = Complex (a - c) (b - d)

    -- Vermenigvuldigen: (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    (*) :: Complex -> Complex -> Complex
    (Complex a b) * (Complex c d) = Complex (a*c - b*d) (a*d + b*c)

    -- Absoluut: √(a² + b²)
    abs :: Complex -> Complex
    abs (Complex a b) = Complex (sqrt (a*a + b*b)) 0

    -- Signum: z / |z|
    signum :: Complex -> Complex
    signum z@(Complex a b) = let Complex r _ = abs z
                             in Complex (a/r) (b/r)

    -- Van Integer: Alleen reëel deel
    fromInteger :: Integer -> Complex
    fromInteger n = Complex (fromInteger n) 0
