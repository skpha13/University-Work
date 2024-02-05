-- reverse a list

solution :: [Int] -> [Int]
solution [] = []
solution (x:xs) = solution xs ++ [x]

test1 = solution [] == []
test2 = solution [1,2,3,4] == [4,3,2,1]
test3 = solution [1,2,2,3,3,2,3,2,3,23,2,3,2,2,32,3,23] == reverse [1,2,2,3,3,2,3,2,3,23,2,3,2,2,32,3,23]

