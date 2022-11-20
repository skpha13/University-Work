l1=int(input("L1="))
l2=int(input("L2="))

r=0
m=l1*l2

while l2!=0:
    r=l1%l2
    l1=l2
    l2=r

m=m//l1//l1

print(m,"de placi de",l1,"cm")