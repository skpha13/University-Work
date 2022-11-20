def p6_a():
    s = input("sir: ")
    t = ""
    num = 0

    for i in s:
        if i.isdigit():
           num = num * 10 + int(i)
        else:
            t = t + i * num
            num = 0

    print(t)

def p6_b():
    s = input("sir: ")
    t = ""

    l = 1

    for i in range(1,len(s)):
        if s[i-1] == s[i]:
            l += 1
        else:
            t = t + str(l) + s[i-1]
            l = 1

    t = t + str(l) + s[i-1]

    print(t)

p6_a()
p6_b()