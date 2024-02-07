-- Collect the internal nodes of a binary tree in a list

data Tree a = Empty | Branch a (Tree a) (Tree a)
              deriving (Show, Eq)

tree4 = Branch 1 (Branch 2 Empty (Branch 4 Empty Empty))
                 (Branch 2 Empty Empty)

collectInternalNodes :: Tree a -> [a]
collectInternalNodes Empty = []
collectInternalNodes (Branch _ Empty Empty) = []
collectInternalNodes (Branch x left Empty) = [x] ++ collectInternalNodes left  
collectInternalNodes (Branch x Empty right) = [x] ++ collectInternalNodes right
collectInternalNodes (Branch x left right) = [x] ++ collectInternalNodes left ++ collectInternalNodes right

test = collectInternalNodes tree4 == [1,2]
