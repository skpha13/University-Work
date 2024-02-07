-- extract a given number of randomly selected elements from a list
import System.Random

-- taken from solutions / doenst work 
solution ls n = do
                gen <- getStdGen
                return $ take n [ ls !! x | x <- randomRs (0, (length ls) -1) gen]

test1 = solution "abcdefgh" 3
