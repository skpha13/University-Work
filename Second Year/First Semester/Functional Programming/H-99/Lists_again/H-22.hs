-- create a list containing all integers within a given range

solution :: Int -> Int -> [Int]
solution left right = [x | x <- [left..right]]

test1 = solution 4 9 == [4,5,6,7,8,9]
