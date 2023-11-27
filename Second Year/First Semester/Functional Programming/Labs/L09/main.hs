data Tree = Empty  -- arbore vid
   | Node Int Tree Tree Tree -- arbore cu valoare de tip Int in radacina si 3 fii
      
extree :: Tree
extree = Node 4 (Node 5 Empty Empty Empty) 
                (Node 3 Empty Empty (Node 1 Empty Empty Empty)) Empty

class ArbInfo t where
  level :: t -> Int -- intoarce inaltimea arborelui; pt un arbore vid
                      -- se considera ca are inaltimea 0
  sumval :: t -> Int -- intoarce suma valorilor din arbore
  nrFrunze :: t -> Int -- intoarce nr de frunze al arborelui
-- level extree
-- 3
-- sumval extree
-- 13
-- nrFrunze extree
-- 2

instance ArbInfo Tree where
    level Empty = 0
    level (Node _ firstSon secondSon thirdSon)= 1 + max (max (level firstSon) (level secondSon)) (level thirdSon)

    sumval Empty = 0
    sumval (Node value firstSon secondSon thirdSon) = value + sumval firstSon + sumval secondSon + sumval thirdSon

    nrFrunze Empty = 0
    nrFrunze (Node _ firstSon secondSon thirdSon) 
        | isLeaf firstSon && isLeaf secondSon && isLeaf thirdSon = 1 + nrFrunze firstSon + nrFrunze secondSon + nrFrunze thirdSon
        | otherwise = nrFrunze firstSon + nrFrunze secondSon + nrFrunze thirdSon
        where isLeaf Empty = True
              isLeaf _ = False

