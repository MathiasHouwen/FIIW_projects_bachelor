import Data.Char (ord)

class Listable a where
  toList :: a -> [Int]

instance Listable Int where
  toList x = [d | d <- [1..x], x `mod` d == 0]

-- Implementeer Listable voor String (lijst van ASCII-waarden)
instance Listable [Char] where
  toList str = map ord str

-- Voorbeeldgebruik:
-- toList (14 :: Int)   --> [1,2,7,14]
-- toList "Hi"          --> [72,105]
