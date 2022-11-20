x=int(input("x="))
n=int(input("n="))
p=int(input("p="))
m=int(input("m="))

s=0

while m>=n:
    s=s+x*n
    m=m-n
    x=(100-p)*x//100

if m>0:
    s += m*x

print(s, "cm")