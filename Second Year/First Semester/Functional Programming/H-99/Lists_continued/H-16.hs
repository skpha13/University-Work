-- drop every N-th element from a list

solution :: Eq a => [a] -> Int -> [a]
solution [] _ = []
solution ls k = solution' ls k 1 

solution' :: Eq a => [a] -> Int -> Int -> [a]
solution' [] _ _ = []
solution' (x:xs) k index 
    | index == 3 = solution' xs k 1
    | otherwise = [x] ++ solution' xs k (index + 1)

test1 = solution "abcdefghik" 3 == "abdeghk"
