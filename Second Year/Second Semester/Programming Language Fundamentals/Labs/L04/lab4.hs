{-# LANGUAGE TypeSynonymInstances #-}
{-# LANGUAGE FlexibleInstances #-}
import Data.Char

newtype Parser a = Parser { parse :: String -> [(a,String)] }

item :: Parser Char
item = Parser (\cs -> case cs of
                "" -> []
                (c:cs) -> [(c,cs)])

instance Monad Parser where
    return a = Parser (\cs -> [(a,cs)])
    p >>= f = Parser (\cs -> concat (map (\(a, cs') -> (parse (f a) cs')) (parse p cs)))

instance Applicative Parser where
    pure = return
    mf <*> ma = do
        f <- mf
        va <- ma
        return (f va)    

instance Functor Parser where              
    fmap f ma = pure f <*> ma   
  
zero :: Parser a
zero = Parser (const [])

psum :: Parser a -> Parser a -> Parser a
psum p q = Parser (\cs -> (parse p cs) ++ (parse q cs))

(<|>) :: Parser a -> Parser a -> Parser a
p <|> q = Parser (\cs -> case parse (psum p q) cs of
                                [] -> []
                                (x:xs) -> [x])

dpsum0 :: Parser [a] -> Parser [a]                       
dpsum0 p = p <|> (return [])

sat :: (Char -> Bool) -> Parser Char
sat p = do
            c <- item
            if p c then return c else zero

char :: Char -> Parser Char
char c = sat (c ==)

string :: String -> Parser String
string [] = return []
string (c:cs) = do
                    pc <- char c
                    prest <- string cs
                    return (pc : prest)

many0 :: Parser a -> Parser [a]
many0 p = dpsum0 (many1 p)

many1 :: Parser a -> Parser [a]
many1 p = do 
    a <- p
    aa <- many0 p
    return (a : aa)

spaces :: Parser String
spaces = many0 (sat isSpace)

token :: Parser a -> Parser a
token p = do
            spaces
            a <- p
            spaces
            return a

symbol :: String -> Parser String
symbol symb = token (string symb)

data AExp = Nu Int | Qid String | PlusE AExp AExp | TimesE AExp AExp | DivE AExp AExp
    deriving (Show, Eq)
    
aexp :: Parser AExp
aexp = plusexp <|> mulexp <|> divexp <|> npexp

npexp = parexp <|> qid <|> integer

parexp :: Parser AExp
parexp = do
            symbol "("
            p <- aexp
            symbol ")"
            return p

look :: Parser (Maybe Char)
look = Parser (\cs -> case cs of
      [] -> [(Nothing, [])]
      (c:cs') -> [(Just c, c:cs')]
    )

digit :: Parser Int
digit = do
          d <- sat isDigit
          return (digitToInt d)

integer :: Parser AExp
integer = do
                  spaces
                  s <- look
                  ss <- do
                            if s == (Just '-') then
                                                  do
                                                    item
                                                    return (-1)
                                               else return 1
                  d <- digitToInt <$> sat isDigit
                  if d == 0 
                    then 
                      return (Nu 0)
                    else 
                      do
                        ds <- many0 digit
                        return (Nu (ss*(asInt (d:ds))))
          where asInt ds = sum [d * (10^p) | (d, p) <- zip (reverse ds) [0..] ]

qid :: Parser AExp
qid = do
            char '\''
            a <- many1 (sat isLetter)
            return (Qid a)

plusexp :: Parser AExp
plusexp = do
            p <- npexp
            symbol "+"
            q <- npexp
            return (PlusE p q)

mulexp :: Parser AExp
mulexp = do
            p <- npexp
            symbol "*"
            q <- npexp
            return (TimesE p q)

divexp :: Parser AExp
divexp = do
            p <- npexp
            symbol "/"
            q <- npexp
            return (DivE p q)


data BExp = BE Bool | LE AExp AExp | NotE BExp | AndE BExp BExp
    deriving Show
    
bexp :: Parser BExp
bexp = lexp <|> notexp <|> andexp <|> npexpb

npexpb = parexpb <|> true <|> false

parexpb :: Parser BExp
parexpb = do
            symbol "("
            p <- bexp
            symbol ")"
            return p

true :: Parser BExp
true = do
            symbol "true"
            return (BE True)

false :: Parser BExp
false = do
            symbol "false"
            return (BE False)

lexp :: Parser BExp
lexp = do
            p <- npexp
            symbol "<="
            q <- npexp
            return (LE p q)

notexp :: Parser BExp
notexp =  do
            symbol "not"
            q <- npexpb
            return (NotE q)

andexp :: Parser BExp
andexp = do
            p <- npexpb
            symbol "&&"
            q <- npexpb
            return (AndE p q)
          
data Stmt = Skip | AtrE String AExp | Seq Stmt Stmt | IfE BExp Stmt Stmt | WhileE BExp Stmt
    deriving Show

stmt :: Parser Stmt
stmt = seqp <|> stmtneseq

stmtneseq :: Parser Stmt
stmtneseq = atre <|> ife <|> whileE <|> skip

atre :: Parser Stmt
atre = do
            spaces
            y <- qid
            case y of
                (Qid x) -> do
                            symbol ":="
                            a <- aexp
                            spaces
                            return (AtrE x a)
                _ -> zero

seqp :: Parser Stmt
seqp = do
            x <- stmtneseq
            rest x
      where rest x = (
                     do
                        symbol ";"
                        y <- stmtneseq
                        rest (Seq x y)
                     )
                     <|> return x

ife :: Parser Stmt
ife = do
          symbol "if"
          symbol "("
          b <- bexp
          symbol ")"
          symbol "{"
          s1 <- stmt
          symbol "}"
          symbol "else"
          symbol "{"
          s2 <- stmt
          symbol "}"
          return (IfE b s1 s2)

whileE :: Parser Stmt
whileE =  do
              symbol "while"
              symbol "("
              b <- bexp
              symbol ")"
              symbol "{"
              s1 <- stmt
              symbol "}"
              return (WhileE b s1)

skip :: Parser Stmt
skip = do
          symbol "skip"
          return Skip

sum_no = unlines ["'n:=100; 's:=0;", "while (not ('n<= 0)) { 's:='s+'n; 'n:= 'n+ (-1)} "]

sum_no_p :: Stmt
sum_no_p = (fst.head) (parse stmt sum_no)

inf_cycle = "'n := 0; while (0 <= 0) {'n := 'n +1}"

inf_cycle_p :: Stmt
inf_cycle_p = (fst.head) (parse stmt inf_cycle)

recall :: String -> [(String, Int)] -> Int
recall s ((t,v):xs) = if t == s then v else recall s xs

update :: String -> Int -> [(String, Int)] -> [(String, Int)]
update s v [] = [(s,v)]
update s v ((t,w):xs) = if t==s then ((s,v):xs) else ((t,w):(update s v xs))

value :: AExp -> [(String, Int)] -> Int
value (Nu n) _ = n
value (Qid t) s = recall t s
value (PlusE e1 e2) s = (value e1 s) + (value e2 s)
value (TimesE e1 e2) s = (value e1 s) * (value e2 s)
value (DivE e1 e2) s = div (value e1 s) (value e2 s)

valueb :: BExp -> [(String, Int)] -> Bool
valueb (BE b) _ = b
valueb (LE e1 e2) s = (value e1 s) <= (value e2 s)
valueb (NotE e) s = not (valueb e s)
valueb (AndE e1 e2) s = (valueb e1 s) && (valueb e2 s)

bssos :: Stmt -> [(String, Int)] -> [(String, Int)]
bssos Skip s = s
bssos (AtrE t e) s = update t (value e s) s
bssos (Seq s1 s2) s = bssos s2 (bssos s1 s)
bssos (IfE be s1 s2) s = if (valueb be s) then (bssos s1 s) else (bssos s2 s)
bssos (WhileE be s1) s = if (valueb be s) then (bssos (WhileE be s1) (bssos s1 s)) else s

prog = sum_no_p

test_bssos = bssos prog []

-- This is where the new stuff starts

-- substitutes the QidX with the string by the arithmetic expression
substaexp :: AExp -> String -> AExp -> AExp
substaexp exp str (Qid var) = if str == var then exp else (Qid var)
substaexp exp str (PlusE left right) = (PlusE (substaexp exp str left) (substaexp exp str right))
substaexp exp str (TimesE left right) = (TimesE (substaexp exp str left) (substaexp exp str right))
substaexp exp str (DivE left right) = (DivE (substaexp exp str left) (substaexp exp str right))
substaexp exp str (Nu nr) = Nu nr

test_substaexp = substaexp (Nu 5) "x" (PlusE (Qid "x") (TimesE (Nu 2) (Qid "y"))) == PlusE (Nu 5) (TimesE (Nu 2) (Qid "y"))

data Assn = BEX Bool | LEX AExp AExp | NotEX Assn | AndEX Assn Assn | DisjInfX [Assn]
    deriving (Show, Eq)

-- value of an assertion relative to a state, similar to valueb
valueassn :: Assn -> [(String, Int)] -> Bool
valueassn (BEX val) _ = val
valueassn (LEX left right) ls = value left ls <= value right ls
valueassn (NotEX assertion) ls = not (valueassn assertion ls)
valueassn (AndEX ass1 ass2) ls = (valueassn ass1 ls) && (valueassn ass2 ls)
valueassn (DisjInfX xs) ls = foldr (||) False (map (`valueassn` ls) xs)

test_valueassn = and
    [ valueassn (BEX True) [] == True
    , valueassn (BEX False) [] == False
    , valueassn (LEX (Nu 2) (Nu 3)) [("x", 5), ("y", 10)] == True
    , valueassn (LEX (Nu 3) (Nu 2)) [("x", 5), ("y", 10)] == False
    , valueassn (NotEX (BEX True)) [] == False
    , valueassn (NotEX (BEX False)) [] == True
    , valueassn (AndEX (BEX True) (BEX True)) [] == True
    , valueassn (AndEX (BEX True) (BEX False)) [] == False
    , valueassn (DisjInfX [BEX False, BEX False, BEX True]) [] == True
    , valueassn (DisjInfX [BEX False, BEX False, BEX False]) [] == False
    ]
 
-- converts a boolean expression to an assertion
convassn :: BExp -> Assn
convassn (BE val) = BEX val
convassn (LE left right) = LEX left right
convassn (NotE exp) = NotEX (convassn exp)
convassn (AndE left right) = AndEX (convassn left) (convassn right)

test_convassn = and
    [ convassn (BE True) == BEX True
    , convassn (BE False) == BEX False
    , convassn (LE (Qid "x") (Qid "y")) == LEX (Qid "x") (Qid "y")
    , convassn (NotE (BE True)) == NotEX (BEX True)
    , convassn (AndE (BE True) (BE False)) == AndEX (BEX True) (BEX False)
    , convassn (AndE (LE (Qid "x") (Qid "y")) (NotE (BE True))) == AndEX (LEX (Qid "x") (Qid "y")) (NotEX (BEX True))
    ]

-- substitutes the QidX with the string by the the arithmetic expression
substassn :: Assn -> String -> AExp -> Assn
substassn (BEX val) _ _ = BEX val
substassn (LEX left right) var exp = LEX (substaexp exp var left) (substaexp exp var right)
substassn (NotEX middle) var exp = NotEX (substassn middle var exp)
substassn (AndEX left right) var exp = AndEX (substassn left var exp) (substassn right var exp) 
substassn (DisjInfX ls) var exp = DisjInfX (map (\x -> substassn x var exp) ls)

test_substassn = and
    [ substassn (BEX True) "x" (Qid "x") == BEX True
    , substassn (LEX (Qid "x") (Qid "y")) "x" (PlusE (Qid "x") (Qid "z")) == LEX (PlusE (Qid "x") (Qid "z")) (Qid "y")
    , substassn (NotEX (BEX True)) "y" (TimesE (Qid "y") (Qid "z")) == NotEX (BEX True)
    , substassn (AndEX (LEX (Qid "x") (Qid "y")) (NotEX (BEX True))) "x" (Qid "z") == AndEX (LEX (Qid "z") (Qid "y")) (NotEX (BEX True))
    , substassn (DisjInfX [BEX False, BEX True, LEX (Qid "x") (Qid "y")]) "x" (Nu 10) == DisjInfX [BEX False, BEX True, LEX (Nu 10) (Qid "y")]
    ]

-- logical or
orx :: Assn -> Assn -> Assn
orx p q = NotEX (AndEX (NotEX p) (NotEX q))

-- extracts the list
extr :: Assn -> [Assn]
extr (DisjInfX li) = li

-- computes the weakest precondition
wp :: Stmt -> Assn -> Assn
wp Skip assn = assn
wp (AtrE var exp) assn = substassn assn var exp 
wp (Seq stmt1 stmt2) assn = wp stmt2 (wp stmt1 assn)
wp (IfE condition stmt1 stmt2) assn = orx (AndEX (convassn condition) (wp stmt1 assn)) (AndEX (NotEX (convassn condition)) (wp stmt2 assn))
wp (WhileE condition stmt) assn = DisjInfX (map p [0..])
    where
        p :: Int -> Assn
        p 0 = AndEX (convassn (NotE condition)) assn 
        p k = AndEX (convassn condition) (wp stmt (p $ k-1))

test1 = valueassn (wp prog (LEX (Qid "s") (Nu 5051))) [] -- should return true

test2 = valueassn (wp prog (LEX (Qid "s") (Nu 5050))) [] -- should return true

test3 = valueassn (wp prog (LEX (Qid "s") (Nu 5049))) [] -- should not terminate

