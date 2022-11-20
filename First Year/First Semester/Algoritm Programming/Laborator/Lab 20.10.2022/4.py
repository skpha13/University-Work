def p4():
    s = input("sir incorect: ")
    t = input("sir corect: ")
    v = ""

    list1 = s.split()
    list2 = t.split()

    k = 0
    for i in range(len(list1)):
        if list1[i] != list2[i] and k<=2:
            k += 1
            v = v + list2[i] + " "
        else:
            v = v + list1[i] + " "
    if k > 2:
        print("textul contine prea multe greseli, doar 2 au fost corectate")
    else:
        print(v)

p4()