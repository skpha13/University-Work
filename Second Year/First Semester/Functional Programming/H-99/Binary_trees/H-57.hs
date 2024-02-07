-- construct a binary search tree from a list of integer numbers

data Tree a = Empty | Branch a (Tree a) (Tree a)
              deriving (Show, Eq)

add :: (Ord a) => Tree a -> a -> Tree a
add Empty value = Branch value Empty Empty
add (Branch key left right) value 
    | value > key = (Branch key left (add right value))
    | otherwise = (Branch key (add left value) right)

construct :: (Ord a) => [a] -> Tree a
construct ls = foldl (\acc x -> add acc x) Empty ls

test1 = construct [3, 2, 5, 7, 1] == Branch 3 (Branch 2 (Branch 1 Empty Empty) Empty) (Branch 5 Empty (Branch 7 Empty Empty))
