-- determine a number is prime

solution :: Int -> Bool
solution nr 
    | nr <= 2 = False
    | otherwise = foldl (\acc x -> acc && (nr `mod` x /= 0)) True [2..(nr-1)] 

test1 = solution 13 == True 
test2 = solution 8 == False
test3 = solution 1 == False
test4 = solution 2 == False
tests = test1 && test2 && test3 && test4
