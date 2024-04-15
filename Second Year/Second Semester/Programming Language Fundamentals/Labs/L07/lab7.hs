data LambdaTerm = Var String | Lam String LambdaTerm | App LambdaTerm LambdaTerm
    deriving Show

-- union of two sets represented as lists
union2 :: (Eq a) => [a] -> [a] -> [a]
union2 x y = x ++ [z | z <- y, notElem z x]

-- variables of a lambda term
var :: LambdaTerm -> [String]
var (Var str) = [str]
var (Lam str lambda) = str : (var lambda)
var (App lambda1 lambda2) = (var lambda1) ++ (var lambda2) 

-- free variables of a lambda term
fv :: LambdaTerm -> [String]
fv (Var str) = [str]
fv (Lam str lambda) = fv lambda
fv (App lambda1 lambda2) = (fv lambda1) ++ (fv lambda2)

-- an endless reservoir of variables
freshvarlist :: [String]
freshvarlist = map ("x" ++) (map show [0..])

-- fresh variable for a term
freshforterm :: LambdaTerm -> String
freshforterm (Var str) = head $ filter (/= str) freshvarlist
freshforterm (Lam str lambda) = head $ filter (`notElem` (str : fv lambda)) freshvarlist
freshforterm (App lambda1 lambda2) =
    let fresh1 = (freshforterm lambda1) 
        fresh2 = (freshforterm lambda2) 
    in head $ filter (`notElem` (fresh1 : fresh2 : (fv lambda1) ++ (fv lambda2))) freshvarlist

-- the substitution operation for lambda terms
subst :: LambdaTerm -> String -> LambdaTerm -> LambdaTerm
subst (Var vr) str lambda2 = if vr == str then lambda2 else (Var vr)
subst (Lam vr lambda1) str lambda2 = if vr == str then lambda2 else (Lam vr (subst lambda1 str lambda2))
subst (App lambda1 lambda2) str lambda3 = (App (subst lambda1 str lambda3) (subst lambda2 str lambda3))

test_subst = subst (Lam "x" (App (Var "y") (Var "x"))) "y" (Var "x")

-- beta reduction in one step
beta1 :: LambdaTerm -> [LambdaTerm]
beta1 = undefined

-- checks whether a term is in normal form
nf :: LambdaTerm -> Bool
nf = undefined

data TermTree = TermTree LambdaTerm [TermTree]
    deriving Show

-- the beta-reduction tree of a lambda term
reductree :: LambdaTerm -> TermTree
reductree t = undefined

-- depth-first traversal of all the nodes in a term tree
df_all :: TermTree -> [LambdaTerm]
df_all (TermTree t l) = undefined

-- just the leaves
df_leaves :: TermTree -> [LambdaTerm]
df_leaves = undefined

-- the left-most outer-most reduction of a term
reduce :: LambdaTerm -> LambdaTerm
reduce = undefined

term1 = App (App (Lam "x" (Lam "y" (App (Var "x") (Var "y")))) (Var "z")) (Var "w")
term2 = App (Lam "x" (App (Lam "y" (Var "x")) (Var "z"))) (Var "w")

test_beta1 = df_leaves (reductree term1)
test_beta2 = df_leaves (reductree term2)

-- a branch of given length in a tree
branch :: Int -> TermTree -> Maybe [LambdaTerm]
branch = undefined
                                
testbranch1 = branch 2 (reductree term1)
                                
testbranch2 = branch 3 (reductree term1)

term_o = Lam "x" (App (Var "x") (Var "x"))
term_O = App term_o term_o

testO = reduce term_O -- should not terminate

term_b = App (App (Lam "x" (Lam "y" (Var "y"))) term_O) (Var "z")

testb = reduce term_b -- should terminate
                                
testbranch3 = branch 10 (reductree term_b)

-- Church numeral of a number
church :: Int -> LambdaTerm
church n = undefined

-- convert from Church numeral back to number
backch :: LambdaTerm -> Int
backch = undefined

-- lambda term for successor
tsucc :: LambdaTerm 
tsucc = undefined

testsucc = backch ((reduce (App tsucc (church 7))))

-- lambda term for addition
tadd :: LambdaTerm
tadd = undefined

testadd = backch ((reduce (App (App tadd (church 7)) (church 8))))

