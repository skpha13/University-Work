factori :: Int -> [Int]
factori n = [ x | x <- [1..n], mod n x == 0 ]

prim :: Int -> Bool
prim n = length (factori n) == 2

numerePrime :: Int -> [Int]
numerePrime n = [ x | x <- [2..n], prim x ]

firstEl :: [(a, b)] -> [a]
firstEl list = map fst list 

sumList :: [[Int]] -> [Int]
sumList list = map sum list

prel2 :: [Int] -> [Int]
prel2 list = map (\x -> if mod x 2 == 0 then x*2 else div x 2) list

ex9 :: Char -> [[Char]] -> [[Char]]
ex9 a list = filter (elem a) list

ex10 :: [Int] -> [Int]
ex10 list = map (\x -> if mod x 2 == 0 then x*x else x) list

ex11 :: [Int] -> [Int]
ex11 list = map ((^2) . fst) (filter (odd . snd) (zip list [1..]))

ex12 :: [[Char]] -> [[Char]]
ex12 list = map (\x -> filter (`elem` "aeiouAEIOU") x) list

mymap :: (a->b) -> [a] -> [b]
mymap f [] = []
mymap f (h:t) = f h : mymap f t

myfilter :: (a->Bool) -> [a] -> [a]
myfilter f [] = []
myfilter f (h:t) = if f h then h:myfilter f t else myfilter f t

