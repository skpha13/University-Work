-- calculate Euler's totient function phi(m)
    -- Euler's so-called totient function phi(m) is defined as the number of 
    -- positive integers r (1 <= r < m) that are coprime to m.

solution :: Int -> Int
solution n = length [x | x <- [1..(n-1)], solution' x n == True]

solution' :: Int -> Int -> Bool
solution' a b = solution'' a b == 1

solution'' :: Int -> Int -> Int
solution'' a b 
    | a == b = a
    | a > b = solution'' (a-b) b
    | a <= b = solution'' a (b-a)

test1 = solution 10 == 4
