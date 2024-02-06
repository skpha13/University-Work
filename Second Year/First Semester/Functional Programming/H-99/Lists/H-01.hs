-- find the last element of the list

solution :: [Int] -> Int
solution [] = 0
solution ls = head $ reverse ls 

test1 = solution [1,2,3,4] == 4
test2 = solution [] == 0
