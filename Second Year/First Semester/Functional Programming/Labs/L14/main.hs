data Point = Pt [Int]
                deriving Show

data Arb = Empty | Node Int Arb Arb 
            deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

getFromInterval :: Int -> Int -> [Int] -> [Int]
getFromInterval x y ls = filter (\it -> it >= x && it <= y) ls
-- [x|x<-ls, a<=x && x<=b]

getFromIntervalMonada :: Int -> Int -> [Int] -> [Int]
getFromIntervalMonada x y ls = do 
                                it <- ls
                                if it >= x && it <= y then return it
                                else []

instance ToFromArb Point where
    fromArb Empty = (Pt [])
    fromArb (Node value left right) = (Pt ((getList (fromArb left)) ++ [value] ++ (getList (fromArb right))))
                                            where getList (Pt ls) = ls 
                                        -- where
                                            -- Pt l = fromArb left
                                            -- Pt r = fromArb right

    toArb (Pt []) = Empty
    toArb (Pt (x:xs)) = Node x (toArb (Pt (filter (<x) xs))) (toArb (Pt (filter (>=x) xs)))



newtype ReaderWriter env a = RW { getRW :: env -> (a, String)}

instance Monad ( ReaderWriter env ) where
    return x = RW (\_ -> (x, ""))
    ma >>= k = RW f where f env =  let (va, log1) = getRW ma env
                                       (vb, log2) = getRW (k va) env
                                    in (vb, log1 ++ log2)
                    
instance Applicative (ReaderWriter env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance Functor (ReaderWriter env) where              
  fmap f ma = pure f <*> ma     