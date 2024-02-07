-- remove the K-th element from a list

solution :: Eq a => [a] -> Int -> (a, [a])
solution (x:xs) k 
    | k == 1 = (x, xs)
    | otherwise = (fst tuple, [x] ++ snd tuple)
        where tuple = solution xs (k-1)

test1 = solution "abcd" 2 == ('b', "acd") 
