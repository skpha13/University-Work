-- eliminate consecutive duplices of list elementsi

solution :: Eq a => [a] -> [a]
solution [] = []
solution ls = foldl (\acc x -> if last acc /= x then acc ++ [x] else acc) [head ls] ls 

test1 = solution "aaaabccaadeeee" == "abcade"
test2 = solution "aaaccacac" == "acacac"
test3 = solution [1,2,23,23,2,1,1,1,1,1] == [1,2,23,2,1]
