data Term = Variable String | FuncSym String [Term]
    deriving (Eq, Show)

union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]
    
union :: (Eq a) => [[a]] -> [a]
union = foldr union2 []

-- returns all variables of a term
var :: Term -> [String]
var (Variable x) = [x]
var (FuncSym f ts) = union (map var ts)

-- substitutes, in a term, a variable by another term
subst :: Term -> String -> Term -> Term
subst (Variable var) str term = if var == str then term else (Variable var)
subst (FuncSym var ls) str term = FuncSym var (map (\t -> subst t str term) ls)

data Equ = Equ Term Term
    deriving Show

data StepResult = FailureS | Stopped | SetS [Equ]
    deriving Show

step1 :: [Equ] -> StepResult
step1 [] = Stopped
step1 (Equ (FuncSym f ss) (FuncSym g ts) : es)
    | f == g = SetS ([Equ t s  | (t, s) <- zip ss ts] ++ es)
step1 (e : es) =
    case step1 es of 
        Stopped -> Stopped
        SetS es' -> SetS (e : es')

step2 :: [Equ] -> StepResult
step2 [] = Stopped
step2 (Equ (FuncSym f ss) (FuncSym g ts) : es)
    | f /= g = FailureS
step2 (e : es) =
    case step2 es of
        Stopped -> Stopped
        FailureS -> FailureS

step3 :: [Equ] -> StepResult
step3 [] = Stopped
step3 (Equ (Variable x) (Variable y) : es)
    | x == y = SetS es
step3 (e : es) =
    case step3 es of
        Stopped -> Stopped
        SetS es' -> SetS (e : es')

step4 :: [Equ] -> StepResult
step4 [] = Stopped
step4 (Equ t@(FuncSym f ss) v@(Variable x) : es) = SetS(Equ v t : es)
step4 (e : es) =
    case step4 es of
        Stopped -> Stopped
        SetS es' -> SetS (e : es')

step5 :: [Equ] -> StepResult
step5 [] = Stopped
step5 (Equ v@(Variable x) t@(FuncSym f ss) : es) 
    | x `elem` var t = FailureS
step5 (e : es) =
    case step5 es of 
        Stopped -> Stopped
        FailureS -> FailureS

-- candidates for "x=t" in step 6 of the algorithm
step6cand :: [Equ] -> [Equ]
step6cand es =
    [ Equ (Variable x) t
        | Equ (Variable x) t <- es
        , notElem x (var t)
        , length [1 | Equ s u <- es, elem x (var s) || elem x (var u)] > 1
    ]

-- substitutes in a list of equations a variable by a term EXCEPT for the equation "variable=term" (as used in step 6 of the algorithm)
substeq :: [Equ] -> String -> Term -> [Equ]
substeq [] _ _ = []
substeq (Equ t1 t2 : es) x t
    | t1 == Variable x && t2 == t = (Equ t1 t2): substeq es x t 
substeq (Equ t1 t2 : es) x t = (Equ (subst t1 x t) (subst t2 x t)) : substeq es x t

step6 :: [Equ] -> StepResult
step6 [] = Stopped
step6 (e : es) =
    case step6 es of
        Stopped -> Stopped
        SetS (Equ (Variable x) t : _) -> SetS (substeq es x t)
                
onestep :: [Equ] -> StepResult
onestep es = case (step1 es) of
              SetS fs -> SetS fs
              Stopped -> case (step2 es) of
                          FailureS -> FailureS
                          Stopped -> case (step3 es) of
                                      SetS fs -> SetS fs
                                      Stopped -> case (step4 es) of
                                                  SetS fs -> SetS fs
                                                  Stopped -> case (step5 es) of
                                                              FailureS -> FailureS
                                                              Stopped ->  case (step6 es) of
                                                                           SetS fs -> SetS fs
                                                                           Stopped -> Stopped

data AllResult = Failure | Set [Equ]
    deriving Show

unify :: [Equ] -> AllResult
unify es = case (onestep es) of
                    Stopped -> Set es
                    FailureS -> Failure
                    SetS fs -> unify fs
                    
eqset1 = [Equ (Variable "z") (FuncSym "f" [Variable "x"]), Equ (FuncSym "f" [Variable "t"]) (Variable "y")]
         -- z=f(x), f(t)=y  --> should have z=f(x), y=f(t)

eqset2 = [Equ (FuncSym "f" [Variable "x", FuncSym "g" [Variable "y"]]) (FuncSym "f" [FuncSym "g" [Variable "z"], Variable "z"])]
         -- f(x,g(y))=f(g(z),z) --> should have x=g(g(y)), z=g(y)

eqset3 = [Equ (FuncSym "f" [Variable "x", FuncSym "g" [Variable "x"], FuncSym "b" []]) (FuncSym "f" [FuncSym "a" [], FuncSym "g" [Variable "z"], Variable "z"])]
          -- f(x,g(x),b)=f(a,g(z),z) --> should return failure