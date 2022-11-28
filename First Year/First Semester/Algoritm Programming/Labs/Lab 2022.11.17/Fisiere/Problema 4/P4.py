import random

file = open("date.in")
date = open("date.out","w")

alfabet = "qwertyuiopasdfghjklzxcvbnm"

for line in file:
    l_cuv = line.split()
    l_cuv[0] = l_cuv[0].lower()
    l_cuv[1] = l_cuv[1].lower()
    email = l_cuv[1] + "." + l_cuv[0] + "@s.unibuc.ro,"
    parola = ""
    for i in range(4):
        parola += random.choice(alfabet)
        if i == 0:
            parola = parola.upper()
    nr = random.randint(1000,9999)
    parola += str(nr)
    date.write(email + parola + "\n")