-- determine the prime factors of a given positive integer

solution :: Int -> [Int]
solution n = solution' n 2

solution' :: Int -> Int -> [Int]
solution' n f 
    | n == 1 = [] 
    | n `mod` f == 0 = [f] ++ solution' (n `div` f) f 
    | otherwise = solution' n (f+1)

test1 = solution 315 == [3, 3, 5, 7]

