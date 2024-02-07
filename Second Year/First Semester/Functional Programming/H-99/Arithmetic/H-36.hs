-- Determine the prime factors and their multiplicities of a given positive integer

-- solution from problem 35
solution :: Int -> [(Int, Int)]
solution n = encode' $ solution' n 2

solution' :: Int -> Int -> [Int]
solution' n f 
    | n == 1 = [] 
    | n `mod` f == 0 = [f] ++ solution' (n `div` f) f 
    | otherwise = solution' n (f+1)

-- solution from problem 10
encode :: Eq a => [a] -> [[a]]
encode [x] = [[x]]
encode (x:xs) = if elem x (head (encode xs))
                  then (x:(head (encode xs))):(tail (encode xs))
                  else [x]:(encode xs)

encode' :: Eq a => [a] -> [(a, Int)]
encode' ls = foldl (\acc x -> acc ++ [(head x, length x)]) [] $ encode ls

test1 = solution 315 == [(3,2),(5,1),(7,1)]
test2 = solution 144 == [(2,4), (3,2)] 
