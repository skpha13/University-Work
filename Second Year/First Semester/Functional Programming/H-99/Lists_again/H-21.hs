-- insert an element at a given position

solution :: Eq a => a -> [a] -> Int -> [a]
solution y (x:xs) 1 = [y] ++ [x] ++ xs
solution y (x:xs) index = [x] ++ solution y xs (index-1)

test1 = solution 'X' "abcd" 2 == "aXbcd"
