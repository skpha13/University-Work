file = open("test.in")
test = open("test.out","w")
nr = 0

for line in file:
    copy = line.replace("\n"," ")
    l_nr = line.replace("*"," ")
    l_nr = l_nr.replace("="," ")
    l_nr = [int(x) for x in l_nr.split()]
    if l_nr[0] * l_nr[1] == l_nr[2]:
        copy += "Corect"
        nr += 1
    else:
        copy += "Gresit " + str(l_nr[0] * l_nr[1])
    copy += "\n"
    test.write(copy)
test.write("Nota " + str(nr + 1) + "\n") 
