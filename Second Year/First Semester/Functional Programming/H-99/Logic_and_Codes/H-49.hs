-- Gray codes
    -- An n-bit Gray code is a sequence of n-bit strings constructed 
    -- according to certain rules.

solution :: Int -> [[Char]]
solution 1 = ["0", "1"]
solution n = (map ("0" ++) $ solution (n-1)) ++ (reverse $ map ("1" ++) $ solution (n-1))

test1 = solution 1 == ["0","1"]
test2 = solution 2 == ["00","01","11","10"]
test3 = solution 3 == ["000","001","011","010","110","111","101","100"]
tests = test1 && test2 && test3
