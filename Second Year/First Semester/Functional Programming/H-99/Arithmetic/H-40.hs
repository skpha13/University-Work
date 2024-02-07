-- Goldbach's conjecture
    -- Goldbach's conjecture says that every positive even number 
    -- greater than 2 is the sum of two prime numbers. 
    -- Example: 28 = 5 + 23. It is one of the most famous facts in number 
    -- theory that has not been proved to be correct in the general case. 
    -- It has been numerically confirmed up to very large numbers 
    -- (much larger than we can go with our Prolog system). 
    -- Write a predicate to find the two prime numbers that sum up to a 
    -- given even integer
    
solution :: Int -> (Int, Int)
solution nr = head [(x,y) | x <- solution39 1 nr, y <- solution39 1 nr, x + y == nr] 

-- solution from problem 39
solution39 :: Int -> Int -> [Int]
solution39 left right = filter prim [left..right] 

prim :: Int -> Bool
prim nr 
    | nr <= 2 = False
    | otherwise = foldl (\acc x -> acc && (nr `mod` x /= 0)) True [2..(nr-1)] 

