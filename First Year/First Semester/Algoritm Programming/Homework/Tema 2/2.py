n=int(input("n="))

i=1
x=float(input())
s=0

while(i<n):
    y=float(input())
    if s<x-y:
        s=x-y
    elif s<y-x:
        s=y-x
    i=i+1

s=s*100
s=int(s)
s=s/100

print(s) 
