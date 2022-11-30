def cautare_cuvant(cuv,nume_fis_out,*nume_fis_in):
    file = open(nume_fis_out,"w")
    for fisier in nume_fis_in:
        file.write(fisier + " ")
        f = open(fisier)
        lines = f.readlines()
        ok = 0
        cuv2 = cuv.capitalize()
        for i in range(len(lines)):
            if cuv in lines[i] or cuv2 in lines[i]:
                ok = 1
                file.write(str(i+1) + " ")
        if ok == 0:
            file.write("Nu exista")
        file.write("\n")

cautare_cuvant("floare","rez.txt","eminescu.txt","paunescu.txt")