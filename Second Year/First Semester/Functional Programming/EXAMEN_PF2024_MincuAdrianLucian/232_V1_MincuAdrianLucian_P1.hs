import Data.Char

-- ========== SOLUTIE FARA MONADA ==========  
encode :: String -> String
encode [] = []
encode (x:xs) 
    | isLower x = [x,x] ++ encode xs
    | isDigit x = "*" ++ encode xs
    | x `elem` "ADT" = [toLower x] ++ encode xs
    | otherwise = [x] ++ encode xs
-- ========================================= 

-- ========== SOLUTIE CU MONADA ==========  
encodeM :: String -> String
encodeM ls = do
             x <- ls
             if isLower x then [x,x] else
                 if isDigit x then "*"
                     else if x `elem` "ADT" then return $ toLower x
                         else return x
-- ======================================= 
