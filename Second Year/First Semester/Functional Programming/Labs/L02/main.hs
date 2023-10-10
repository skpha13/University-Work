import Data.List

poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a * x ** 2 + b * x + c

eeny :: Integer -> String
eeny x 
    | mod x 2 == 0 = "eeny"
    | otherwise = "meeny"

fizzbuzz :: Integer -> String

 -- GUARDS METHOD --
{- 
fizzbuzz x 
    | mod x 15 == 0 = "FizzBuzz"
    | mod x 3 == 0 = "Fizz"
    | mod x 5 == 0 = "Buzz"
    | otherwise = ""
-}

 -- IF METHOD --
fizzbuzz x = if mod x 15 == 0
                then "FizzBuzz"
            else if mod x 3 == 0
                    then "Fizz"
                else if mod x 5 == 0
                        then "Buzz"
                    else ""

tribonacci :: Integer -> Integer
tribonacci 1 = 1
tribonacci 2 = 1
tribonacci 3 = 2
tribonacci n = tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3)

binomial :: Integer -> Integer -> Integer
binomial n 0 = 1
binomial 0 k = 0
binomial n k = binomial (n-1) k + binomial (n-1) (k-1)

verifL :: [Integer] -> Bool
verifL xs
    | mod (length xs) 2 == 0 = True
    | otherwise = False

takeFinal :: [Integer] -> Integer -> [Integer]
takeFinal xs n = drop (length xs - fromInteger n) xs

remove :: [Integer] -> Integer -> [Integer]
remove xs n = take (fromInteger n) xs ++ drop (fromInteger n + 1) xs

semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)
    | even h = h `div` 2 : t'
    | otherwise = t'
    where t' = semiPareRec t

myreplicate :: Integer -> Integer -> [Integer]
myreplicate 0 _ = []
myreplicate n v = v : myreplicate (n-1) v

sumImp :: [Integer] -> Integer
sumImp [] = 0
sumImp (h:t)
    | even h = sumImp t
    | otherwise = h + sumImp t

totalLen :: [String] -> Int
totalLen [] = 0
totalLen (h:t)
    | h !! 0 == 'A' = length h + totalLen t
    | otherwise = totalLen t