import Data.Maybe

data Expr = Const Int
        | Expr :+: Expr
        | Expr :*: Expr
        deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int
        | Node Operation Tree Tree
        deriving (Eq, Show)

-- ========== EXPRESSIONS ========== 

evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (x :+: y) = evalExp x + evalExp y
evalExp (x :*: y) = evalExp x * evalExp y

instance Show Expr where
        show (Const x) = show x
        show (e1 :+: e2) = "(" ++ show e1 ++ " + " ++ show e2 ++ ")"
        show (e1 :*: e2) = "(" ++ show e1 ++ " * " ++ show e2 ++ ")"

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)

test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16
-- =================================

-- ========== TREES ========== 
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node op tree1 tree2) = case op of
                                Add -> evalArb tree1 + evalArb tree2
                                Mult -> evalArb tree1 * evalArb tree2

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16

expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (expr1 :+: expr2) = Node Add (expToArb expr1) (expToArb expr2) 
expToArb (expr1 :*: expr2) = Node Mult (expToArb expr1) (expToArb expr2) 

test1 = expToArb exp1 == arb1
test2 = expToArb exp2 == arb2
test3 = expToArb exp3 == arb3
test4 = expToArb exp4 == arb4
-- =================================

-- ========== BINARY SEARCH TREES ==========
data IntSearchTree value
        = Empty
        | BNode
                (IntSearchTree value) -- elemente cu cheia mai mica
                Int -- cheia elementului
                (Maybe value) -- valoarea elementului
                (IntSearchTree value) -- elemente cu cheia mai mare

lookup' :: Int -> IntSearchTree value -> Maybe value
lookup' x Empty = Nothing
lookup' x (BNode leftTree key mvalue rightTree) = if x == key && not(isNothing mvalue) then mvalue
                                                        else if x > key then lookup' x rightTree
                                                        else lookup' x leftTree

exampleTree = BNode (BNode Empty 1 (Just 1) Empty) 2 (Just 2) (BNode Empty 3 (Just 3) Empty)

-- returns sorted keys because of inorder traversal property of binary search trees
keys :: IntSearchTree value -> [Int]
keys Empty = []
keys (BNode leftTree key mvalue rightTree) = x ++ [key] ++  y
                                                where x = keys leftTree
                                                      y = keys rightTree 

values :: IntSearchTree value -> [value]
values Empty = []
values (BNode leftTree key mvalue rightTree) = if not(isNothing mvalue) 
                                                then values leftTree ++ [mvalue] ++ values rightTree
                                                else values leftTree ++ values rightTree

-- =================================