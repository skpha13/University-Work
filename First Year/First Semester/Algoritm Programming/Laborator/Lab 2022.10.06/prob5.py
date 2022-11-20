import math

a=int(input("a="))
b=int(input("b="))
c=int(input("c="))

delta = b*b - 4*a*c

if delta<0:
    print("nicio solutie")
elif delta==0:
    x=(-b+math.sqrt(delta))/2*a
    print("x1=",x)
elif delta>0:
    x=(-b+math.sqrt(delta))/2*a
    y=(-b-math.sqrt(delta))/2*a
    print("x1=",x)
    print("x2=",y)
