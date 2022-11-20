n=int(input("n="))
i=2

mx1=int(input())
mx2=int(input())

if(mx2>mx1):
    mx1,mx2= mx2,mx1

while i<n:
    x=int(input())
    if(x>mx1):
        mx2=mx1
        mx1=x
    elif x>mx2 and x!=mx1:
        mx2=x
    i=i+1

if mx1==mx2:
    print("Imposibil")
else:
    print(mx2,mx1)
