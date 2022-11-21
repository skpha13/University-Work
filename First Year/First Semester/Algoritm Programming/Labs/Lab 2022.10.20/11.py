def p11_a():
    def codare():
        s = input("text: ")
        t = ""
        voc = "aeiouAEIOU"

        for i in s:
            if i in voc:
                t = t + i + "p" + i.lower()
            else:
                t = t + i
        
        print(t,end="\n")

    def decodare():
        s = input("text: ")
        voc = "aeiouAEIOU"

        for i in s:
            if i in voc:
                s = s.replace("p"+i,"",1)

        print(s)

    codare()
    decodare()


def p11_b():
    def codare():
        s = input("text: ")
        s = s.split("-")
        t = ""

        def spatii(text):
            v = ""
            text = text.split()
            for i in text:
                v = v + i + "p" + i[len(i)-1] + " "
            
            return v[:-1]

        for i in s:
            if " " in i:
                i = spatii(i)
                t = t + i + "-"
                continue
            t = t + i + "p" + i[len(i)-1] + "-"
        t = t[:-1]

        print(t)

    def decodare():
        s = input("text: ")
        s = s.split("-")
        t = ""

        for i in s:
            i = i[:-2]
            t = t + i + "-"
        t = t[:-1]

        s = ""
        t = t.split()
        x = t[len(t)-1][-2:]

        for i in t:
            i = i[:-2]
            s = s + i + " "
        
        s = s[:-1]
        s = s + x
        print(s)

    codare()
    decodare()


p11_a()
p11_b()