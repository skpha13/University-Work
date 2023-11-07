data Fruct =
    Mar String Bool
    | Portocala String Int

getNumeFruct :: Fruct -> String
getNumeFruct (Portocala x _) = x
getNumeFruct (Mar x _) = x

getNrFelii :: Fruct -> Int
getNrFelii (Portocala _ x) = x

hasViermi :: Fruct -> Bool
hasViermi (Mar _ x) = x

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

data Linie = L [Int]
   deriving Show
data Matrice = M [Linie]
   deriving Show

test_verif1 = verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10 == False
test_verif2 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25 == True

testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == True
testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == False

testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) == False
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]]) == True

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia fruct = elem (getNumeFruct fruct) ["Tarocco", "Moro", "Sanguinello"]

test_ePortocalaDeSicilia1 = ePortocalaDeSicilia (Portocala "Moro" 12) == True

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia ls = foldr (\x acc -> getNrFelii x + acc) 0 (filter ePortocalaDeSicilia ls)

test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52

isMar :: Fruct -> Bool
-- isMar f = case f of 
--     Mar _ _ -> True
--     Portocala _ _ -> False 
isMar (Mar _ _) = True
isMar (Portocala _ _) = False

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi (h:t)
    | isMar h && hasViermi h = 1 + nrMereViermi t
    | otherwise = nrMereViermi t

test_nrMereViermi = nrMereViermi listaFructe == 2

vorbeste :: Animal -> String
vorbeste (Pisica _) = "meow!"
vorbeste (Caine _ _) = "woof!"

rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ x) = Just x


getLinie :: Linie -> [Int]
getLinie (L x) = x

getMatrice :: Matrice -> [[Int]]
getMatrice (M l) = map getLinie l

verifica :: Matrice -> Int -> Bool
verifica m n = foldr (&&) True (map (== n) (map sum (getMatrice m)))

onlyPositive :: [Int] -> Bool
onlyPositive ls = if sum (map (\x -> if x < 0 then 1 else 0) ls) == 0 then True else False

doarPozN :: Matrice -> Int -> Bool
doarPozN m n = foldr (\x acc -> snd x && acc) True ( filter (\x -> fst x == n) $ zip (map length $ getMatrice m) (map onlyPositive $ getMatrice m))  

corect :: Matrice -> Bool
corect m = let ls = (map length $ getMatrice m) in 
            if sum (map (\x -> if x /= (ls !! 1) then 1 else 0) ls) == 0 then True else False