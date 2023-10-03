a = 123

double :: Integer -> Integer
double x = x + x

fact :: Integer -> Integer
fact 1 = 1
fact n = n * fact (n-1)

checkDouble :: Integer -> Integer -> String
checkDouble x y = if (x > y*2) 
                    then "true"
                    else "false"

maxElem :: [Integer] -> Integer -> Integer
maxElem [] mx = mx
maxElem (h:t) mx = if (h > mx)
                    then maxElem t h 
                    else maxElem t mx

getMax :: [Integer] -> Integer
getMax x = maxElem x 0

-- 1 from H-99
myLast :: [Integer] -> Integer
myLast [] = 0
myLast (h:t) = if (t == []) 
                    then h
                    else myLast t

-- 2 from H-99
myButLast :: [Integer] -> Integer
myButLast [] = 0
myButLast [x,y] = x
myButLast (h:t) = myButLast t