-- Geometrische figuren
data Point = Point Double Double deriving (Show, Eq)
data Rectangle = Rectangle Point Point deriving (Show, Eq) -- (minX, minY) tot (maxX, maxY)
data Circle = Circle Point Double deriving (Show, Eq) -- middelpunt + straal

-- Type class voor overlappende figuren
class Geometric a where
  overlaps :: a -> a -> Bool
  boundingBox :: a -> a -> a
  area :: a -> Double
  contains :: a -> a -> Bool

  -- Default: figuur omsluit andere figuur als het zijn bounding box bevat
  contains a b = overlaps (boundingBox a b) a

-- Helpers
inRectangle :: Point -> Rectangle -> Bool
inRectangle (Point x y) (Rectangle (Point x1 y1) (Point x2 y2)) =
  x >= x1 && x <= x2 && y >= y1 && y <= y2

distance :: Point -> Point -> Double
distance (Point x1 y1) (Point x2 y2) =
  sqrt ((x2 - x1)^2 + (y2 - y1)^2)

-- Implementatie voor rechthoeken
instance Geometric Rectangle where
  overlaps (Rectangle (Point x1 y1) (Point x2 y2))
           (Rectangle (Point x3 y3) (Point x4 y4)) =
    not (x2 < x3 || x4 < x1 || y2 < y3 || y4 < y1)

  boundingBox (Rectangle (Point x1 y1) (Point x2 y2))
              (Rectangle (Point x3 y3) (Point x4 y4)) =
    Rectangle (Point (min x1 x3) (min y1 y3)) (Point (max x2 x4) (max y2 y4))

  area (Rectangle (Point x1 y1) (Point x2 y2)) =
    abs (x2 - x1) * abs (y2 - y1)

-- Implementatie voor cirkels
instance Geometric Circle where
  overlaps (Circle c1 r1) (Circle c2 r2) =
    distance c1 c2 <= r1 + r2

  boundingBox (Circle (Point x1 y1) r1) (Circle (Point x2 y2) r2) =
    let minX = min (x1 - r1) (x2 - r2)
        maxX = max (x1 + r1) (x2 + r2)
        minY = min (y1 - r1) (y2 - r2)
        maxY = max (y1 + r1) (y2 + r2)
    in Circle (Point ((minX + maxX)/2) ((minY + maxY)/2)) ((maxX - minX)/2)

  area (Circle _ r) = pi * r * r

  contains (Circle c1 r1) (Circle c2 r2) =
    distance c1 c2 + r2 <= r1
