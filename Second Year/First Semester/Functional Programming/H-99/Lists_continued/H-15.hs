-- replicate the elements of a list given number of times

solution :: Eq a => [a] -> Int -> [a]
solution ls nr = foldl (\acc x -> acc ++ replicate nr x) [] ls

test1 = solution "abc" 3 == "aaabbbccc"
test2 = solution "a" 100 == replicate 100 'a'
