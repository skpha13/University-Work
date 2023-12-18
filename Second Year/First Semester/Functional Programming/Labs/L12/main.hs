data Cow = Cow {
        name :: String
        , age :: Int
        , weight :: Int
        } deriving (Eq, Show)

noEmpty :: String -> Maybe String
noEmpty s
    | length s == 0 = Nothing
    | otherwise = Just s

noNegative :: Int -> Maybe Int
noNegative x
    | x < 0 = Nothing
    | otherwise = Just x

test21 = noEmpty "abc" == Just "abc"
test22 = noNegative (-5) == Nothing 
test23 = noNegative 5 == Just 5 

cowFromString :: String -> Int -> Int -> Maybe Cow
cowFromString s x y
    | (noEmpty s /= Nothing) && (noNegative x /= Nothing) && (noNegative y /= Nothing)  = Just (Cow s x y)
    | otherwise = Nothing

test24 = cowFromString "Milka" 5 100 == Just (Cow {name = "Milka", age = 5, weight = 100})

cowFromStringFmap :: String -> Int -> Int -> Maybe Cow
cowFromStringFmap s x y = Cow <$> (noEmpty s) <*> (noNegative x) <*> (noNegative y) 



newtype Name = Name String deriving (Eq, Show)
newtype Address = Address String deriving (Eq, Show)

data Person = Person Name Address
    deriving (Eq, Show)

validateLength :: Int -> String -> Maybe String
validateLength l s
    | length s < l = Just s
    | otherwise = Nothing

test31 = validateLength 5 "abc" == Just "abc"
mkName :: String -> Maybe Name
mkName s = Name <$> (validateLength 100 s) 

mkAddress :: String -> Maybe Address
mkAddress s = Address <$> (validateLength 100 s) 

test32 = mkName "Gigel" ==  Just (Name "Gigel")
test33 = mkAddress "Str Academiei" ==  Just (Address "Str Academiei")

mkPerson :: String -> String -> Maybe Person
mkPerson s1 s2 = Person <$> (mkName s1) <*> (mkAddress s2) 

test34 = mkPerson "Gigel" "Str Academiei" == Just (Person (Name "Gigel") (Address "Str Academiei"))



data List a = Nil
            | Cons a (List a)
        deriving (Eq, Show)

instance Functor List where
    fmap _ Nil = Nil
    fmap f (Cons a l) = (Cons (f a) (fmap f l)) 

instance Applicative List where
    pure x = (Cons x Nil)   
    (<*>) Nil _ = Nil
    (<*>) _ Nil = Nil
    (<*>) (Cons x y) l = append (fmap x l) (y <*> l)
                            where 
                                append :: List a -> List a -> List a
                                append Nil Nil = Nil
                                append ls Nil = ls
                                append (Nil) ls = ls
                                append (Cons x l) ls = (Cons x (append l ls))

f = Cons (+1) (Cons (*2) Nil)
v = Cons 1 (Cons 2 Nil)
test1 = (f <*> v) == Cons 2 (Cons 3 (Cons 2 (Cons 4 Nil)))

