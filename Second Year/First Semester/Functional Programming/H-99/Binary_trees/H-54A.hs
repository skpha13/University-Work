-- check whether a given term represents a binary tree

data Tree a = Empty | Branch a (Tree a) (Tree a)
              deriving (Show, Eq)

-- since the only possibilities of a branch is to have at maximum
-- 2 subtrees then every tree we get is a binary tree
