newtype AM a = AM { getAM :: (Maybe a, String) } deriving Show

instance Monad AM where
    return x = AM (Just x, "") 
    ma >>= k = AM f where
        f = let (va, log1) = getAM ma  
                result = case va of
                            Nothing -> (Nothing, log1)
                            Just x -> let AM (vb, log2) = k x
                                      in (vb, log1 ++ " " ++ log2)
            in result

instance Functor AM where
    fmap f ma = f <$> ma

instance Applicative AM where
    pure = return
    mf <*> ma = do
        f <- mf
        f <$> ma

testAM :: AM Int
testAM = ma >>= f
    where ma = AM (Just 7, "ana are mere")
          f x = AM (if even x then Just x else Nothing, "si pere!")

-- AM { getAM = (Nothing, "ana are mere si pere!") }
