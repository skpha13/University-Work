-- rotate  a list N places to the left

solution :: Eq a => [a] -> Int -> [a]
solution ls index = solution' ls (number + 1) (length ls) ++ solution' ls 0 number 
                    where number = if index < 0 then length ls + index
                                    else index

solution' :: Eq a => [a] -> Int -> Int -> [a]
solution' ls left right = foldl (\acc x -> if snd x >= left && snd x <= right then acc ++ [fst x] else acc) [] (zip ls [1..])

test1 = solution ['a','b','c','d','e','f','g','h'] 3 == "defghabc"
test2 = solution ['a','b','c','d','e','f','g','h'] (-2) == "ghabcdef"
