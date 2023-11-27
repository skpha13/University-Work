-- =========== ARBORI ===========
data Tree = Empty  -- arbore vid
   | Node Int Tree Tree Tree -- arbore cu valoare de tip Int in radacina si 3 fii
      
extree :: Tree
extree = Node 4 (Node 5 Empty Empty Empty) 
                (Node 3 Empty Empty (Node 1 Empty Empty Empty)) Empty

class ArbInfo t where
  level :: t -> Int -- intoarce inaltimea arborelui; pt un arbore vid
                      -- se considera ca are inaltimea 0
  sumval :: t -> Int -- intoarce suma valorilor din arbore
  nrFrunze :: t -> Int -- intoarce nr de frunze al arborelui
-- level extree
-- 3
-- sumval extree
-- 13
-- nrFrunze extree
-- 2

instance ArbInfo Tree where
    level Empty = 0
    level (Node _ firstSon secondSon thirdSon)= 1 + max (max (level firstSon) (level secondSon)) (level thirdSon)

    sumval Empty = 0
    sumval (Node value firstSon secondSon thirdSon) = value + sumval firstSon + sumval secondSon + sumval thirdSon

    nrFrunze Empty = 0
    nrFrunze (Node _ firstSon secondSon thirdSon) 
        | isLeaf firstSon && isLeaf secondSon && isLeaf thirdSon = 1 + nrFrunze firstSon + nrFrunze secondSon + nrFrunze thirdSon
        | otherwise = nrFrunze firstSon + nrFrunze secondSon + nrFrunze thirdSon
        where isLeaf Empty = True
              isLeaf _ = False
-- =============================

-- ========== VECTORI ==========
class Scalar a where
    zero :: a
    one :: a
    adds :: a -> a -> a
    mult :: a -> a -> a
    negates :: a -> a
    recips :: a -> a

class (Scalar a) => Vector v a where
    zerov :: v a
    onev :: v a
    addv :: v a -> v a -> v a -- adunare vector
    smult :: a -> v a -> v a  -- inmultire cu scalare
    negatev :: v a -> v a -- negare vector

instance Scalar Int where
    zero = 0
    one = 1
    adds x y = x + y
    mult x y = x * y
    negates x = (-1) * x
    recips 0 = 0
    recips x = div 1 x

intAdds :: Int -> Int -> Int
intAdds x y = adds x y

intMult :: Int -> Int -> Int
intMult x y = mult x y

intNegates :: Int -> Int
intNegates x = negates x

intRecips :: Int -> Int
intRecips x = recips x


data Bidimensional a = Vect2 a a 
data Tridimensional a = Vect3 a a a

instance (Scalar a) => Vector Bidimensional a where
    zerov = Vect2 zero zero
    onev = Vect2 one one
    addv (Vect2 x1 y1) (Vect2 x2 y2) = Vect2 (adds x1 x2) (adds y1 y2)
    smult scalar (Vect2 x y) = Vect2 (mult scalar x) (mult scalar y)
    negatev (Vect2 x y) = Vect2 (negates x) (negates y)


instance (Show a, Scalar a) => Show (Bidimensional a) where
    show (Vect2 x y) = "(" ++ show x ++ ", " ++ show y ++ ")"

exVect2 = (negatev (Vect2 2 3) :: Bidimensional Int)

instance (Scalar a) => Vector Tridimensional a where
    zerov = Vect3 zero zero zero
    onev = Vect3 one one one 
    addv (Vect3 x1 y1 z1) (Vect3 x2 y2 z2) = Vect3 (adds x1 x2) (adds y1 y2) (adds z1 z2)
    smult scalar (Vect3 x y z) = Vect3 (mult scalar x) (mult scalar y) (mult scalar z)
    negatev (Vect3 x y z) = Vect3 (negates x) (negates y) (negates z)

exVect3 = (negatev (Vect3 4 5 6) :: Tridimensional Int)

instance (Show a, Scalar a) => Show (Tridimensional a) where
    show (Vect3 x y z) = "(" ++ show x ++ ", " ++ show y ++ ", " ++ show z ++ ")"
-- =============================