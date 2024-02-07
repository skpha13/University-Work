-- split a list into two parts, the legnth of the first part is given

solution :: Eq a => [a] -> Int -> ([a],[a])
solution [] _ = ([],[])
solution ls 0 = ([],ls)
solution (x:xs) k = ([x] ++ (fst $ solution xs (k-1)), snd $ solution xs (k-1)) 

test1 = solution "abcdefghijk" 3 == ("abc", "defghijk")
