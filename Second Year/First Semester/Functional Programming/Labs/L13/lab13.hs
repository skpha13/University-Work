{- Monada Maybe este definita in GHC.Base 

instance Monad Maybe where
  return = Just
  Just va  >>= k   = k va
  Nothing >>= _   = Nothing


instance Applicative Maybe where
  pure = return
  mf <*> ma = do
    f <- mf
    va <- ma
    return (f va)       

instance Functor Maybe where              
  fmap f ma = pure f <*> ma   
-}

pos :: Int -> Bool
pos  x = if (x>=0) then True else False

fct :: Maybe Int ->  Maybe Bool
fct  mx =  mx  >>= (\x -> Just (pos x))

fctdo :: Maybe Int -> Maybe Bool
fctdo mx = do 
            x <- mx 
            Just(pos x)

addM :: Maybe Int -> Maybe Int -> Maybe Int
addM mx my = do
              x <- mx
              y <- my
              (Just (x+y))

addMonad :: Maybe Int -> Maybe Int -> Maybe Int
addMonad mx my = mx >>= (\x -> (my >>= \y -> return (x+y)))

addMPattern :: Maybe Int -> Maybe Int -> Maybe Int
addMPattern Nothing _ = Nothing
addMPattern _ Nothing = Nothing
addMPattern (Just x) (Just y) = (Just (x+y))


cartesian_product xs ys = xs >>= ( \x -> (ys >>= \y-> return (x,y)))
cartesian_product_do xs ys = do
                              x <- xs
                              y <- ys
                              return (x,y)

prod f xs ys = [f x y | x <- xs, y<-ys]
proddo f xs ys = do
                  x <- xs
                  y <- ys
                  return (f x y)

myGetLine :: IO String
myGetLine = getChar >>= \x ->
      if x == '\n' then
          return []
      else
          myGetLine >>= \xs -> return (x:xs)

myGetLineDo = do
              it <- getChar
              if it == '\n' then return []
              else do
                rest <- myGetLineDo
                return (it: rest)

prelNo noin =  sqrt noin

ioNumber = do
     noin  <- readLn :: IO Float
     putStrLn $ "Intrare\n" ++ (show noin)
     let  noout = prelNo noin
     putStrLn $ "Iesire"
     print noout

isNumberSubsequence = readLn >>= \noin -> 
                      putStrLn ("Intrare\n" ++ (show noin)) >>
                      let noout = prelNo noin in putStrLn ("Iesire") >>
                      print noout


data Person = Person { name :: String, age :: Int }

showPersonN :: Person -> String
showPersonN (Person name _) = "NAME: " ++ name 
showPersonA :: Person -> String
showPersonA (Person _ age) = "AGE: " ++ (show age)

{-
showPersonN $ Person "ada" 20
"NAME: ada"
showPersonA $ Person "ada" 20
"AGE: 20"
-}

showPerson :: Person -> String
showPerson p = "(" ++ (showPersonN p) ++ ", " ++ (showPersonA p) ++ ")" 

{-
showPerson $ Person "ada" 20
"(NAME: ada, AGE: 20)"
-}


newtype Reader env a = Reader { runReader :: env -> a }

instance Monad (Reader env) where
  return x = Reader (\_ -> x)
  ma >>= k = Reader f
    where f env = let a = runReader ma env
                  in  runReader (k a) env

instance Applicative (Reader env) where
  pure = return
  mf <*> ma = do
    f <- mf
    a <- ma
    return (f a)       

instance Functor (Reader env) where              
  fmap f ma = pure f <*> ma    

ask :: Reader env env 
ask = Reader id

mshowPersonN ::  Reader Person String
mshowPersonN = do
                (Person name _) <- ask
                return ("NAME: " ++ name)
mshowPersonA ::  Reader Person String
mshowPersonA = do
                (Person _ age) <- ask
                return ("AGE: " ++ (show age))
mshowPerson ::  Reader Person String
mshowPerson = do
                (Person name age) <- ask
                return ("(NAME: " ++ name ++ ", AGE:" ++ (show age) ++ ")")
{-
runReader mshowPersonN  $ Person "ada" 20
"NAME:ada"
runReader mshowPersonA  $ Person "ada" 20
"AGE:20"
runReader mshowPerson  $ Person "ada" 20
"(NAME:ada,AGE:20)"
-}