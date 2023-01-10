s = input()
i = 1

for y in range(len(s)//2):
    # for x in range(i):
    #     print(" ",end="")
    print(s[i:-i].center(len(s)))
    i += 1