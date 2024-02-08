-- collect the nodes at a given level in a list

data Tree a = Empty | Branch a (Tree a) (Tree a)
              deriving (Show, Eq)

tree4 = Branch 1 (Branch 2 Empty (Branch 4 Empty Empty))
                 (Branch 2 Empty Empty)

collectNodesAtLevel :: Tree a -> Int -> [a]
collectNodesAtLevel tree desiredLevel = collectNodesAtLevel' tree desiredLevel 1

collectNodesAtLevel' :: Tree a -> Int -> Int -> [a]
collectNodesAtLevel' Empty _ _ = []
collectNodesAtLevel' (Branch x left right) desiredLevel level 
    | level == desiredLevel = [x] 
    | otherwise = collectNodesAtLevel' left desiredLevel (level+1) ++ collectNodesAtLevel' right desiredLevel (level+1)

test1 = collectNodesAtLevel tree4 2 == [2,2]
