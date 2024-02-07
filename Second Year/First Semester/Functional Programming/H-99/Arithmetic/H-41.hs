-- A list of even numbers and their Goldbach compositions in a given range

solution :: Int -> Int -> [(Int, Int)]
solution left right = [solution40 x | x <- [left..right], x `mod` 2 == 0] 

-- solution from problem 40
solution40 :: Int -> (Int, Int)
solution40 nr = head [(x,y) | x <- solution39 1 nr, y <- solution39 1 nr, x + y == nr] 

-- solution from problem 39
solution39 :: Int -> Int -> [Int]
solution39 left right = filter prim [left..right] 

prim :: Int -> Bool
prim nr 
    | nr <= 2 = False
    | otherwise = foldl (\acc x -> acc && (nr `mod` x /= 0)) True [2..(nr-1)] 

test1 = solution 9 20 == [(3,7),(5,7),(3,11),(3,13),(5,13),(3,17)]
