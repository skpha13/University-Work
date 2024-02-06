-- duplicate the elements of a list

solution :: Eq a => [a] -> [a]
solution ls = foldl (\acc x -> acc ++ [x] ++ [x]) [] ls

test1 = solution [1,2,3] == [1,1,2,2,3,3]
test2 = solution [1] == [1,1]
test3 = solution "abcd" == "aabbccdd"
