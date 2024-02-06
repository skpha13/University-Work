-- decode a run-length encoded list

data Encoded a = Single a | Multiple Int a deriving (Eq, Show) 

solution :: [Encoded a] -> [a]
solution ls = concatMap (constructList) ls
                where constructList (Single x) = [x]
                      constructList (Multiple number x) = replicate number x 

test1 = solution [Multiple 4 'a', Single 'b', Multiple 2 'c', Multiple 2 'a', Single 'd', Multiple 4 'e'] == "aaaabccaadeeee" 
