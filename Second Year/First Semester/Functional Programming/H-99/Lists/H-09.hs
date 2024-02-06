-- pack consecutive duplicates of list elements into sublists

solution :: Eq a => [a] -> [[a]]
solution [x] = [[x]]
solution (x:xs) = if elem x (head (solution xs))
                  then (x:(head (solution xs))):(tail (solution xs))
                  else [x]:(solution xs)

test1 = solution ['a', 'a', 'a', 'a', 'b', 'c', 'c', 'a', 'a', 'd', 'e', 'e', 'e', 'e'] == ["aaaa","b","cc","aa","d","eeee"]
test2 = solution ['a','b','c'] == ["a", "b", "c"]
test3 = solution [1,1,1,1,1] == [[1,1,1,1,1]]
