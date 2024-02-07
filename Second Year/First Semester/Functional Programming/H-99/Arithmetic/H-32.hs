-- determine the greates common divisor of two positive integers

solution :: Int -> Int -> Int
solution a b 
    | a == b = a
    | a > b = solution (a-b) b
    | a <= b = solution a (b-a)

test1 = solution 36 63 == 9
