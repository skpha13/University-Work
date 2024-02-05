-- find the last-but-one (or second-last) element of a list

solution :: [Int] -> Int
solution [] = 0
solution ls = (reverse ls) !! 1 

test1 = solution [1,2,3,4] == 3
test2 = solution [] == 0
