sumaPatrate :: [Integer] -> Integer
sumaPatrate ls = foldr (+) 0 $ map (\x -> x*x) $ filter (\x -> mod x 2 /= 0) ls

sumaPatrateLambda :: [Integer] -> Integer
sumaPatrateLambda ls = foldr (\x acc -> x*x + acc) 0 $ filter (\x -> mod x 2 /= 0) ls
-- daca era foldl -> \acc x 

verificaTrue :: [Bool] -> Bool
verificaTrue ls = foldr (&&) True ls

allVerifies :: (Int -> Bool) -> [Int] -> Bool
allVerifies f ls = foldr (&&) True $ map f ls

anyVerifies :: (Int -> Bool) -> [Int] -> Bool
anyVerifies f ls = foldr (||) False $ map f ls

mapFoldr :: (a->b) -> [a] -> [b]
mapFoldr f ls = foldr (\x acc -> f x : acc) [] ls

filterFoldr :: (a->Bool) -> [a] -> [a]
filterFoldr f ls = foldr (\x acc -> if f x then x : acc else acc) [] ls

listToInt :: [Integer] -> Integer
listToInt (h:t) = foldl (\x acc -> x*10 + acc) h t

rmChar :: Char -> String -> String
rmChar ch ls = filter (\x -> x /= ch) ls

rmCharRec :: String -> String -> String
rmCharRec [] ls = ls
rmCharRec _ [] = []
rmCharRec (h:t) xs = rmCharRec t $ rmChar h xs

rmCharsFold :: String -> String -> String
rmCharsFold ls xs = foldr rmChar xs ls

myReverse :: [Int] -> [Int]
myReverse ls = foldr (\x acc -> acc ++ [x]) [] ls  

myElem :: Int -> [Int] -> Bool
myElem x ls = foldr (||) False $ map ( == x) ls

-- [(1,2),(2,3),(3,4)]
-- ([1,2,3],[2,3,4])
myUnzip :: [(a,b)] -> ([a],[b])
myUnzip ls = (foldl (\x acc -> x ++ [fst acc]) [] ls, foldl (\x acc -> x ++ [snd acc]) [] ls)

union :: [Int] -> [Int] -> [Int]
union ls xs = foldr (\x acc -> x : acc) ls xs

-- nub import from Data.List ne asigura ca nu se repeta elemente

intersect :: [Int] -> [Int] -> [Int]
intersect ls xs = foldr (\x acc -> if elem x ls then x : acc else acc) [] xs

-- permutari
asezareElPoz :: a -> [a] -> Int -> [a]
asezareElPoz x [] _ = [x]
asezareElPoz x l poz = take poz l ++ [x] ++ drop poz l

permCuOLista :: a -> [a] -> [[a]]
permCuOLista h t = [asezareElPoz h t c | c <- [0..length t]]

permListeDeListe :: a -> [[a]] -> [[a]]
permListeDeListe _ [] = []
permListeDeListe x (h:t) = permCuOLista x h ++ permListeDeListe x t

permutations :: [Int] -> [[Int]]
permutations ls = foldr (\x acc -> permListeDeListe x acc) [[]] ls