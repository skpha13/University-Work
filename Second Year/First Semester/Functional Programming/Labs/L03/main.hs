import Data.Char

rev :: [Char] -> [Char]
rev [] = []
rev (x:xs) = rev(xs) ++ [x]

palindrom :: [Char] -> Bool
palindrom [] = True
palindrom a 
    | a == rev a = True
    | otherwise = False

adunaVocale :: [Char] -> Int
adunaVocale [] = 0
adunaVocale (x:xs) 
    | elem x "aeiouAEIOU"= 1 + adunaVocale xs
    | otherwise = adunaVocale xs 


nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (x:xs) 
    | palindrom x = adunaVocale x + nrVocale xs
    | otherwise = nrVocale xs

f :: Int -> [Int] -> [Int]
f _ [] = []
f a (x:xs) 
    | mod x 2 == 0 = x : a : f a xs
    | otherwise = x : f a xs

semiPareComp :: [Int] -> [Int]
semiPareComp l = [ x `div` 2 | x <- l, even x ]

divizori :: Int -> [Int]
divizori n = [ x | x <- [1..n], mod n x == 0 ]

listaDiv :: [Int] -> [[Int]]
listaDiv [] = []
listaDiv (x:xs) = divizori x : listaDiv xs

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec _ _ [] = []
inIntervalRec x y (h:t)
    | h >= x && h <= y = h : inIntervalRec x y t
    | otherwise = inIntervalRec x y t

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp _ _ [] = []
inIntervalComp x y l = [ a | a <- l, a >= x && a <= y ]

pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t) 
    | h > 0 = 1 + pozitiveRec t
    | otherwise = pozitiveRec t

pozitiveComp :: [Int] -> Int
pozitiveComp l = length [x | x <- l, x > 0]

pozitiiHelper :: [Int] -> Int -> [Int]
pozitiiHelper [] _ = []
pozitiiHelper (h:t) x 
    | mod x 2 == 1 = h : pozitiiHelper t (x+1)
    | otherwise = pozitiiHelper t (x+1)

pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = pozitiiHelper l 0 

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [snd x | x <- zip l [0..(length l - 1)], rem (fst x) 2 == 1]

multiDigitsRec :: [Char] -> Int
multiDigitsRec [] = 1
multiDigitsRec (h:t)
    | isDigit h = digitToInt h * multiDigitsRec t
    | otherwise = multiDigitsRec t

produs :: [Int] -> Int
produs [] = 1
produs (h:t) = h * produs t

multiDigitsComp :: [Char] -> Int
multiDigitsComp l = produs [digitToInt x | x <- l, isDigit x]

takeFinal :: [a] -> Int -> [a]
takeFinal xs n = drop (length xs - fromInteger n) xs

permPoz :: [a] -> Int -> a -> [a]
permPoz [] _ = _
permPoz l x = (take (x-1) l ++ l !! x) ++ (drop (length l - fromInteger x) l) 

-- pemrutariHelper :: a -> [a] -> [[a]]
-- pemrutariHelper x [] = [x]
-- pemrutariHelper x l = 

-- permutari :: [a] -> [a]
-- permutari [] = []
-- permutari l =