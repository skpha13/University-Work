-- determine whether two positive integers are coprime

solution :: Int -> Int -> Bool
solution a b = solution' a b == 1

solution' :: Int -> Int -> Int
solution' a b 
    | a == b = a
    | a > b = solution' (a-b) b
    | a <= b = solution' a (b-a)

test1 = solution 35 64 == True
test2 = solution 2 4 == False
tests = test1 && test2
