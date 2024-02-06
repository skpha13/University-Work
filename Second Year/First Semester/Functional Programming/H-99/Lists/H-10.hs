-- run-length encoding of a list
    -- use the result of problem 9 to impletemt the so called
    -- run-length encoding data compression method
        -- Consecutive duplicates of elements are encoded as lists (N E) 
        -- where N is the number of duplicates of the element E.

solution :: Eq a => [a] -> [[a]]
solution [x] = [[x]]
solution (x:xs) = if elem x (head (solution xs))
                  then (x:(head (solution xs))):(tail (solution xs))
                  else [x]:(solution xs)

solution' :: Eq a => [a] -> [(Int, a)]
solution' ls = foldl (\acc x -> acc ++ [(length x, head x)]) [] $ solution ls

test1 = (solution' "aaaabccaadeeee") == [(4,'a'),(1,'b'),(2,'c'),(2,'a'),(1,'d'),(4,'e')]
test2 = (solution' "abc") == [(1,'a'), (1,'b'), (1,'c')] 
test3 = (solution' [1,1,1,1,1]) == [(5,1)] 
