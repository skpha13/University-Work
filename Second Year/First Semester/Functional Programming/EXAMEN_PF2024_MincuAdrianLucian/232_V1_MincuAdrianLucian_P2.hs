import Data.Char

data Pereche a b = MyP a b deriving Show
newtype Lista a = MyL [a] deriving Show

class MyOp m where
    myOp :: (a -> b) -> (b -> a) -> m (Pereche a b) -> m (Pereche b a)

instance MyOp Lista where
    myOp _ _ (MyL []) = MyL []
    myOp f g (MyL ((MyP a b):xs)) = MyL ([MyP (f a) (g b)] ++ getList (myOp f g (MyL xs)))
        where 
            getList (MyL ls) = ls 

lp :: Lista (Pereche Int Char)
lp = MyL [MyP 97 'a', MyP 3 'b', MyP 100 'd'] 

