import Data.Maybe

-- ========== CLASS COLLECTION ========== 
class Collection c where
    empty :: c key value
    singleton :: key -> value -> c key value
    insert
        :: Ord key
        => key -> value -> c key value -> c key value
    clookup :: Ord key => key -> c key value -> Maybe value
    delete :: Ord key => key -> c key value -> c key value
    keys :: c key value -> [key]
    values :: c key value -> [value]
    toList :: c key value -> [(key, value)]
    fromList :: Ord key => [(key,value)] -> c key value
    keys t = map fst $ toList t
    values t = map snd $ toList t 
    fromList (x:xs) 
        | length xs == 0 = singleton (fst x) (snd x)
        | otherwise = insert (fst x) (snd x) (fromList xs) 

 
-- functioneaza ca data dar poate sa aiba doar un singur constructor
newtype PairList k v = PairList { getPairList :: [(k,v)] }

instance (Show k, Show v) => Show(PairList k v) where
    show (PairList p) = show p

instance Collection PairList where
    empty = PairList []
    singleton k v = PairList [(k, v)]
    insert k v (PairList []) = singleton k v
    insert k v (PairList (x:xs))
        | k == fst x = PairList ((k,v) : xs)
        | length xs == 0 = PairList (x : (k,v) :  xs)
        | otherwise =  insert k v (PairList xs)
    toList (PairList []) = []
    toList (PairList (x:xs)) = x : (toList $ PairList xs)
    clookup _ (PairList []) = Nothing
    clookup key (PairList ((k, v):xs)) 
        | key == k = Just v
        | otherwise = clookup key (PairList xs)
    delete _ (PairList []) = empty
    delete key (PairList ((k,v):xs))
        | key == k = PairList xs
        | otherwise = PairList((k, v) : getPairList (delete key (PairList xs)))

data SearchTree key value
    = Empty
    | BNode
        (SearchTree key value)
        key
        (Maybe value)
        (SearchTree key value)

instance Collection SearchTree where
    empty = Empty
    singleton key value = (BNode Empty key (Just value) Empty)
    insert key value Empty = singleton key value
    insert key value (BNode leftTree k mvalue rightTree) =  if key == k then (BNode leftTree key (Just value) rightTree)  
                                                                else if key < k then (BNode (insert key value leftTree) k mvalue rightTree) 
                                                                else (BNode leftTree k mvalue (insert key value rightTree)) 
    delete _ Empty = Empty
    delete key (BNode leftTree k mvalue rightTree) = if key == k then (BNode leftTree key Nothing rightTree)
                                                        else if key < k then (BNode (delete key leftTree) k mvalue rightTree)
                                                        else (BNode leftTree k mvalue (delete key rightTree))
    clookup _ Empty = Nothing
    clookup key (BNode leftTree k mvalue rightTree) = if key == k && not(isNothing mvalue) then mvalue
                                                        else if key > k then clookup key rightTree
                                                        else clookup key leftTree
    toList Empty = []
    toList (BNode leftTree key mvalue rightTree) = case mvalue of
                                                    Just val -> toList leftTree ++ [(key, val)] ++ toList rightTree
                                                    Nothing -> toList leftTree ++ toList rightTree
    fromList ls = foldr (\x acc -> insert (fst x) (snd x) acc) Empty ls
 
instance (Show key, Show value) => Show (SearchTree key value) where
        show Empty = ""
        show (BNode Empty key _ Empty) = "(" ++ (show key) ++ ")"
        show (BNode Empty key _ rightTree) = "((" ++ (show key) ++ ")" ++ show rightTree ++ ")"
        show (BNode leftTree key _ Empty) = "(" ++ show leftTree ++ "(" ++ (show key) ++ "))"
        show (BNode leftTree key _ rightTree) ="(" ++ show leftTree ++ "(" ++ (show key) ++ ")" ++ show rightTree ++ ")"

tree = (singleton 1 2 :: SearchTree Int Int)
-- ======================================

-- ========== PUNCTE PUNCTE =============
data Punct = Pt [Int]

data Arb = Vid | F Int | N Arb Arb
          deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

helperShowPunct :: [Int] -> String
helperShowPunct [] = ""
helperShowPunct (x:xs) = ", " ++ show x ++ helperShowPunct xs

instance Show Punct where
    show (Pt []) = "()"
    show (Pt [x]) = "(" ++ show x ++ ")"
    show (Pt (x:xs)) = "(" ++ show x ++ helperShowPunct xs ++ ")"

getListaPuncte :: Punct -> [Int]
getListaPuncte (Pt list) = list

instance ToFromArb Punct where
    toArb (Pt []) = Vid
    toArb (Pt (x:xs)) = N (F x) (toArb (Pt xs))
    fromArb Vid = Pt []
    fromArb (F x) = Pt [x]
    fromArb (N arb1 arb2) = Pt $ (getListaPuncte $ fromArb arb1) ++ (getListaPuncte $ fromArb arb2)
-- ======================================

-- ========== FIGURI GEOMETRICE ==========
data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
    perimeter :: (Floating a) => g a -> a
    area :: (Floating a) => g a -> a

instance GeoOps Geo where
    perimeter (Square x) = x * 4
    perimeter (Rectangle x y) = 2 * (x + y)
    perimeter (Circle x) = 2 * pi * x
    area (Square x) = x * x
    area (Rectangle x y) = x * y
    area (Circle x) = pi * x * x

instance (Floating a, Eq a) => Eq (Geo a) where
    (Square x) == (Square y) = perimeter (Square x) == perimeter (Square y)
    (Rectangle x y) == (Rectangle a b) = perimeter (Rectangle x y) == perimeter (Rectangle a b)
    (Circle x) == (Circle y) = perimeter (Circle x) == perimeter (Circle y)
-- =======================================