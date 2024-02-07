--  Calculate Euler's totient function phi(m) (improved)
    -- See Problem 34 for the definition of Euler's totient 
    -- function. If the list of the prime factors of a number 
    -- m is known in the form of problem 36 then the function 
    -- phi(m) can be efficiently calculated as follows: 
    -- Let ((p1 m1) (p2 m2) (p3 m3) ...) be the list of prime factors (and their multiplicities) of a given number m. Then phi(m) can be calculated with the following formula:
         -- phi(m) = (p1 - 1) * p1 ** (m1 - 1) * 
         --          (p2 - 1) * p2 ** (m2 - 1) * 
         --          (p3 - 1) * p3 ** (m3 - 1) * ...

solution :: Int -> Int
solution nr = foldl (\acc x -> acc * (fst x - 1) * (fst x) ^ (snd x -1)) 1 (solution36 nr)

-- solution from problem 36
solution36 :: Int -> [(Int, Int)]
solution36 n = encode' $ solution36' n 2

solution36' :: Int -> Int -> [Int]
solution36' n f 
    | n == 1 = [] 
    | n `mod` f == 0 = [f] ++ solution36' (n `div` f) f 
    | otherwise = solution36' n (f+1)

-- solution36 from problem 10
encode :: Eq a => [a] -> [[a]]
encode [x] = [[x]]
encode (x:xs) = if elem x (head (encode xs))
                  then (x:(head (encode xs))):(tail (encode xs))
                  else [x]:(encode xs)

encode' :: Eq a => [a] -> [(a, Int)]
encode' ls = foldl (\acc x -> acc ++ [(head x, length x)]) [] $ encode ls

test1 = solution 10 == 4
