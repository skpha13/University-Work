-- extract a slice from a list

solution :: Eq a => [a] -> Int -> Int -> [a]
solution ls left right = foldl (\acc x -> if snd x >= left && snd x <= right then acc ++ [fst x] else acc) [] (zip ls [1..])

test1 = solution ['a','b','c','d','e','f','g','h','i','k'] 3 7 == "cdefg"
