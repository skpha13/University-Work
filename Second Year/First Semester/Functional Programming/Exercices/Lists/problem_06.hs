-- find out whether a list is a palindrome 

solution :: Eq a => [a] -> Bool
solution [] = True
solution ls = ls == reverse ls

test1 = solution [1,2,4,8,16,8,4,2,1] == True
test2 = solution "madamimadam" == True
test3 = solution [1,2,3] == False
