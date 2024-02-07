-- A list of prime numbers in a given range

solution :: Int -> Int -> [Int]
solution left right = filter prim [left..right] 

prim :: Int -> Bool
prim nr 
    | nr <= 2 = False
    | otherwise = foldl (\acc x -> acc && (nr `mod` x /= 0)) True [2..(nr-1)] 

test1 = solution 10 20 == [11, 13, 17, 19]
