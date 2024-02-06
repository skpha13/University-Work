-- find the number of elements in a list

solution :: [Int] -> Int
solution [] = 0
solution (x:xs) = 1 + solution xs 

test1 = solution [] == 0
test2 = solution [1,2,3,4] == 4
test3 = solution [1] == 1
