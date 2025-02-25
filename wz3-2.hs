-- Oefening 1
ontbinden :: Integral b => b -> [(b, b)]
ontbinden n = [ (x, n `div` x) | x <- [1..floor (sqrt (fromIntegral n))], n `mod` x == 0 ]

-- Oefening 2
triple n = [ (x,y,z) | x <- [1..n], y <- [1..n], 
                                    let z = floor (sqrt (fromIntegral (x*x + y*y))),
                                    z <= n, x*x + y*y == z*z]

-- Oefening 3
lijst :: (Num t, Enum t) => t -> a -> [a]
lijst n x = [x | _ <- [1..n]]

-- Oefening 4
driehoek :: [(Int, Int, Int)]
driehoek = pythagoreanTriangles 24

pythagoreanTriangles :: Int -> [(Int, Int, Int)]
pythagoreanTriangles p = 
    [ (a, b, c) 
    | a <- [1..p], b <- [a..p], c <- [b..p], 
      a + b + c == p, 
      a^2 + b^2 == c^2]

-- Oefening 5
paar :: Integral b => b -> [(b, b)]
paar n = [(x, y) | x <- [1..n], y <- [1..n], x < y, gcd x y == 1]