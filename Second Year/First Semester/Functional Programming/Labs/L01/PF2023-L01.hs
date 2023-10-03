import Data.List

myInt = 31415926535897932384626433832795028841971693993751058209749445923

double :: Integer -> Integer
double x = x+x


--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y

max3 x y z = let
             u = maxim x y
             in (maxim  u z)

               
