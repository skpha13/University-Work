-- ========== P1 ==========  
data Piece = One | Two | Empty
    deriving (Show, Eq)

data Table = Table [Piece] [Piece] [Piece] 
    deriving (Show, Eq)

validTable :: Table -> Bool
validTable (Table ls xs ys) 
    | length ls /= 8 || length xs /= 8 || length ys /= 8 = False
    | otherwise = fst result <= 9 && snd result <= 9 
    where result = countPlayerPieces (Table ls xs ys)

countPlayerPieces :: Table -> (Int, Int)
countPlayerPieces (Table ls xs ys) = (length $ filter (== One) $ ls ++ xs ++ ys,
                                      length $ filter (== Two) $ ls ++ xs ++ ys)

table1 = Table [One, Two, One, Two, Empty, Empty, Empty, Empty] [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty] [Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty] 
-- ========================  

-- ========== P2 ========== 
data Position = P (Int, Int)

getList :: Table -> Int -> [Piece]
getList (Table ls xs ys) 0 = ls
getList (Table ls xs ys) 1 = xs
getList (Table ls xs ys) 2 = ys
getList _ _ = []

isConnected :: Position -> Position -> Bool
isConnected (P (x1, x2)) (P (y1, y2))
    | x2 == 0 && x1 == y1 = y2 == x2 + 1 || y2 == 7
    | mod x2 2 == 0 && x1 == y1 = y2 == x2 + 1 || y2 == x2 - 1
    | mod x2 2 == 1 && x1 /= y1 = x2 == y2 && abs (x1 - y1) == 1
    | mod x2 2 == 1 && x1 == y1 = y2 == x2 + 1 || y2 == x2 - 1
    | otherwise = False

move :: Table -> Position -> Position -> Maybe Table
move (Table ls xs ys) (P (x1, x2)) (P (y1, y2)) 
    | (getList (Table ls xs ys) x1) !! x2 == Empty = Nothing
    | (getList (Table ls xs ys) y1) !! y2 /= Empty = Nothing 
    | isConnected (P (x1, x2)) (P (y1, y2)) = Just (Table ls xs ys) -- TODO(1)
    | otherwise = Nothing
-- TODO(1) : at this point I just stopped, it's too much game logic to do
-- ======================== 

-- ========== P3 ==========  
data EitherWriter a = EW { getValue :: Either String (a, String) }

instance Monad EitherWriter where
    return a = EW (Right (a, ""))
    ma >>= k = EW $ case getValue ma of
                Left error -> Left error
                Right (a, str) -> getValue (k a)

instance Applicative EitherWriter
instance Functor EitherWriter
-- ========================  
