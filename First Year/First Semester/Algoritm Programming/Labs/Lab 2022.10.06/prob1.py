n = int(input("n="))
aux=n
ogl=0
while n>0:
    ogl=ogl*10+n%10
    n=n//10

if(ogl==aux):
    print("palindrom")
else:
    print("nu e palindrom")