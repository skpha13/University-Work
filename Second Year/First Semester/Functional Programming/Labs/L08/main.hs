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
        | otherwise =  (insert k v (PairList xs))
    toList (PairList []) = []
    toList (PairList (x:xs)) = x : (toList $ PairList xs)