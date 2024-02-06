-- modify the result of problem 10 in such way that if an element
-- has no duplicates it is simply copied into the result list

data Encoded a = Single a | Multiple Int a deriving (Eq, Show) 

solution :: Eq a => [a] -> [[a]]
solution [x] = [[x]]
solution (x:xs) = if elem x (head (solution xs))
                  then (x:(head (solution xs))):(tail (solution xs))
                  else [x]:(solution xs)

solution' :: Eq a => [a] -> [Encoded a]
solution' ls = foldl (\acc x -> if length x == 1 then acc ++ [Single $ head x] else acc ++ [Multiple (length x) (head x)]) [] $ solution ls

test1 = (solution' "aaaabccaadeeee") == [Multiple 4 'a', Single 'b', Multiple 2 'c', Multiple 2 'a', Single 'd', Multiple 4 'e'] 

