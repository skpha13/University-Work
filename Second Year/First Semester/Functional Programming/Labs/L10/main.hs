import Data.List (nub)
import Data.Maybe (fromJust)

-- ========== VECTORI ==========
type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  | Prop :->: Prop
  | Prop :<->: Prop
  deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: ((Not (Var "P")) :&: (Not (Var "Q")))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: (((Not (Var "P")) :|: Var "Q") :&: ((Not (Var "P")) :|: (Not (Var "R"))))

instance Show Prop where
    show (Var nume) = nume
    show F = show "False"
    show T = show "True"
    show (Not prop) = "(~" ++ show prop ++ ")"
    show (prop1 :|: prop2) = "(" ++ show prop1 ++ "||" ++ show prop2 ++ ")"
    show (prop1 :&: prop2) = "(" ++ show prop1 ++ "&" ++ show prop2 ++ ")"
    show (prop1 :->: prop2) = "(" ++ show prop1 ++ "->" ++ show prop2 ++ ")"
    show (prop1 :<->: prop2) = "(" ++ show prop1 ++ "<->" ++ show prop2 ++ ")"

test_ShowProp :: Bool
test_ShowProp =
    show (Not (Var "P") :&: Var "Q") == "((~P)&Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a,b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval _ [] = False
eval F _ = False
eval T _ = True
eval (Var nume) env = impureLookup nume env
eval (prop1 :|: prop2) env = eval prop1 env || eval prop2 env
eval (prop1 :&: prop2) env = eval prop1 env && eval prop2 env 
eval (prop1 :->: prop2) env = let x = eval prop1 env 
                                  y = eval prop2 env 
                                in
                                if ((x == True && y == True)
                                    || (x == False && y == True)
                                    || (x == False && y == False)) then True
                                    else False
eval (prop1 :<->: prop2) env = let x = eval prop1 env
                                   y = eval prop2 env
                                in 
                                    (x && y ) || (not x && not y)
eval (Not prop) env = not (eval prop env)

test = eval (Not (Var "P") :&: Var "Q") [("P",False),("Q",True)] == True

test_eval = eval  (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

variabile :: Prop -> [Nume]
variabile (Var nume) = [nume]
variabile ( x :|: y ) = nub ( (variabile x) ++ (variabile y) )
variabile ( x :&: y ) = nub ( (variabile x) ++ (variabile y) )
variabile (Not x) = variabile x
variabile _ = []

test_variabile =
  variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

envs :: [Nume] -> [Env]
envs [] = [[]]
envs (x:xs) = [(x, val) : env |  val <- [False, True], env <- envs xs] 

test_envs = 
    envs ["P", "Q"]
    ==
    [ [ ("P",False)
      , ("Q",False)
      ]
    , [ ("P",False)
      , ("Q",True)
      ]
    , [ ("P",True)
      , ("Q",False)
      ]
    , [ ("P",True)
      , ("Q",True)
      ]
    ]

satisfiabila :: Prop -> Bool
satisfiabila prop = foldr (\x acc -> (eval prop x) || acc) False (envs (variabile prop))

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

valida :: Prop -> Bool
valida prop = foldr (\x acc -> (eval prop x) && acc) True (envs (variabile prop))

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True

echivalenta :: Prop -> Prop -> Bool
echivalenta prop1 prop2 = foldr (\x acc -> (eval (prop1 :<->: prop2) x) && acc) True envs (variabile prop1)
 
test_echivalenta1 =
  True
  ==
  (Var "P" :&: Var "Q") `echivalenta` (Not (Not (Var "P") :|: Not (Var "Q")))
test_echivalenta2 =
  False
  ==
  (Var "P") `echivalenta` (Var "Q")
test_echivalenta3 =
  True
  ==
  (Var "R" :|: Not (Var "R")) `echivalenta` (Var "Q" :|: Not (Var "Q"))
-- =============================