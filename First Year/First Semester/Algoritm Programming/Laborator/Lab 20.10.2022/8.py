def p8():
    def verify():
        s = input("nume complet: ")

        def cifre():
            return any(c.isdigit() for c in s)
        if cifre():
            return 0

        s = s.split()

        if len(s) > 4:
            return 0

        if len(s) >= 3 and s.count("-") == 0:
            return 0

        num = s[0].count("-")
        if num >= 2:
            return 0
        num = s[1].count("-")
        if num >= 2:
            return 0

        nume = s[0].split("-")
        prenume = s[1].split("-")

        if len(nume) > 2 or len(prenume) > 2:
            return 0

        for x in nume:
            if x[0] >= "a" and x[0] <= "z" or len(x)<3:
                return 0
        for x in prenume:
            if x[0] >= "a" and x[0] <= "z" or len(x)<3:
                return 0

        return 1
    if verify():
        print("Nume corect")
    else:
        print("Nume incoret")

p8()