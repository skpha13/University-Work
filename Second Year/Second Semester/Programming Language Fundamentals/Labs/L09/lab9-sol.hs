data PCFTerm = Var String | Lam String PCFTerm | App PCFTerm PCFTerm | Zero | Suc PCFTerm | IfZ PCFTerm PCFTerm String PCFTerm | Fix String PCFTerm
    deriving Show

-- union of two sets represented as lists
union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]

-- variables of a PCF term
var :: PCFTerm -> [String]
var (Var x) = [x]
var (Lam x t) = union2 (var t) [x]
var (App t s) = union2 (var t) (var s)
var Zero = []
var (Suc t) = var t
var (IfZ n t w s) = union2 [w] (union2 (var n) (union2 (var t) (var s)))
var (Fix x t) = union2 (var t) [x]

-- free variables of a PCF term
fv :: PCFTerm -> [String]
fv (Var x) = [x]
fv (Lam x t) = [y | y <- fv t, y /= x]
fv (App t s) = union2 (fv t) (fv s)
fv Zero = []
fv (Suc t) = fv t
fv (IfZ n t w s) = union2 (fv n) (union2 (fv t) [y | y <- fv s, y /= w])
fv (Fix x t) = [y | y <- fv t, y /= x]

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- fresh variable for a PCF term
freshforterm :: PCFTerm -> String
freshforterm t = head [x | x <- freshvarlist, notElem x (var t)]

-- the substitution operation for PCF terms
subst :: PCFTerm -> String -> PCFTerm -> PCFTerm
subst (Var x) y t
    | x == y        = t
    | otherwise     = Var x
subst (Lam x s) y t
    | x == y        = Lam x s
    | elem x (fv t) = let z = freshforterm (Lam y (App s t)) in Lam z (subst (subst s x (Var z)) y t)
    | otherwise     = Lam x (subst s y t)
subst (App s u) y t = App (subst s y t) (subst u y t)
subst Zero _ _      = Zero
subst (Suc s) y t   = Suc (subst s y t)
subst (IfZ n s w u) y t
    | w == y        = IfZ (subst n y t) (subst s y t) w u
    | elem w (fv t) = let z = freshforterm (Fix y (App u t)) in IfZ (subst n y t) (subst s y t) z (subst (subst u w (Var z)) y t)
    | otherwise     = IfZ (subst n y t) (subst s y t) w (subst u y t)
subst (Fix x s) y t
    | x == y        = Fix x s
    | elem x (fv t) = let z = freshforterm (Fix y (App s t)) in Fix z (subst (subst s x (Var z)) y t)
    | otherwise     = Fix x (subst s y t)

-- eager isValue
isValueE :: PCFTerm -> Bool
isValueE Zero = True
isValueE (Suc x) = isValueE x
isValueE (Lam _ _) = True
isValueE _ = False

-- eager beta reduction in one step
beta1E :: PCFTerm -> Maybe PCFTerm
beta1E (Suc t) = fmap Suc (beta1E t)
beta1E (IfZ Zero s w t) = Just s
beta1E (IfZ (Suc m) s w t) | isValueE (Suc m) = Just (subst t w m)
beta1E (IfZ n s w t) = case beta1E n of
                                Just p -> Just (IfZ p s w t)
                                Nothing -> Nothing
beta1E (App (Lam x s) t) | isValueE t = Just (subst s x t)
beta1E (App s t) = case beta1E s of
                        Just u -> Just (App u t)
                        Nothing -> if isValueE s then (case beta1E t of
                                                            Just u -> Just (App s u)
                                                            Nothing -> Nothing)
                                                 else Nothing
beta1E (Fix w t) = Just (subst t w (Fix w t))
beta1E _ = Nothing

-- the ultimate reduction of a term
reduceE :: PCFTerm -> PCFTerm
reduceE t = case beta1E t of
                    Just s -> reduceE s
                    Nothing -> t

-- natural numbers in PCF
number :: Int -> PCFTerm
number 0 = Zero
number n = Suc (number (n-1))

-- conversion from PCF back to natural numbers
backnr :: PCFTerm -> Int
backnr Zero = 0
backnr (Suc n) = (backnr n) + 1

-- PCF term for addition
tadd :: PCFTerm
tadd = Fix "f" (Lam "x" (Lam "y" (IfZ (Var "y") (Var "x") "w" (Suc (App (App (Var "f") (Var "x")) (Var "w"))))))

testadd = backnr (reduceE (App (App tadd (number 2)) (number 3)))

-- PCF term for subtraction
tsub :: PCFTerm
tsub = Fix "f" (Lam "x" (Lam "y" (IfZ (Var "y") (Var "x") "u" (IfZ (App (App (Var "f") (Var "x")) (Var "u")) Zero "w" (Var "w")))))

testsub1 = backnr (reduceE (App (App tsub (number 15)) (number 8)))

testsub2 = backnr (reduceE (App (App tsub (number 7)) (number 8)))

-- PCF term for GCD
tgcd :: PCFTerm
tgcd = Fix "f" (Lam "m" (Lam "n" (IfZ (Var "n") (Var "m") "u" (IfZ (Var "m") (Var "n") "v" (IfZ (App (App tsub (Var "m")) (Var "n")) (App (App (Var "f") (Var "m")) (App (App tsub (Var "n")) (Var "m"))) "w" (App (App (Var "f") (Suc (Var "w"))) (Var "n")))))))

testgcd = backnr (reduceE (App (App tgcd (number 30)) (number 36)))

-- PCF term for minimization
tmu :: PCFTerm
tmu = App (Fix "m" (Lam "n" (Lam "f" (IfZ (App (Var "f") (Var "n")) (Var "n") "w" (App (App (Var "m") (Suc (Var "n"))) (Var "f")))))) Zero

testmu1 = backnr (reduceE (App tmu (Lam "x" (App (App tsub (number 15)) (Var "x")))))
testmu2 = backnr (reduceE (App tmu (Lam "x" (App (App tadd (number 15)) (Var "x"))))) -- should not terminate