def p10():
    a = input("primul cuvant: ")
    b = input("al doilea cuvant: ")

    litere = "qwertyuiopasdfghjklzxcvbnm"

    def verify():
        for x in litere:
            if a.count(x) != b.count(x):
                return 0
        return 1

    if verify():
        print("anagrame")
    else:
        print("nu sunt anagrame")

p10()