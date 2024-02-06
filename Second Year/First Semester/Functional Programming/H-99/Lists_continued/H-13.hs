-- implement run-length encoding method directly without using sublists

data Encoded a = Single a | Multiple Int a deriving (Eq, Show) 

solution :: Eq a => [a] -> [Encoded a]
solution [] = []
solution (x:xs) = solution' x 1 xs

solution' :: Eq a => a -> Int -> [a] -> [Encoded a]
solution' x nr [] = [encode x nr]
solution' x nr (y:ys) = if x == y then solution' x (nr+1) ys
                        else (encode x nr) : (solution' y 1 ys) 

encode :: a -> Int -> Encoded a
encode x 1 = Single x
encode x nr = Multiple nr x

test1 = solution "aaaabccaadeeee" == [Multiple 4 'a',Single 'b',Multiple 2 'c', Multiple 2 'a',Single 'd',Multiple 4 'e']     
