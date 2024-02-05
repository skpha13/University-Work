-- find the K-th element of a list

solution1 :: [Int] -> Int -> Int
solution1 _ 0 = 0
solution1 [] _ = 0
solution1 ls k = ls !! (k-1)

test1 = solution1 [1,2,3,4] 2 == 2
test2 = solution1 [1,2,2,3,121,3,24,1,421,4] 5 == 121
test3 = solution1 [] 2 == 0
