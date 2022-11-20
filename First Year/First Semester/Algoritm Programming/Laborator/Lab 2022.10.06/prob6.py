n=int(input("n="))

aux=n
c=aux%10
aux=aux//10
p=10
mx=c
mn=c

while aux!=0:
    if aux%10 >= c:
        mx = (aux%10)*p + mx
        mn = mn*10 + aux%10
    else:
        mx = mx*10 + aux%10
        mn = (aux%10)*p + mn
    p*=10
    c=aux%10
    aux=aux//10

print(mx)
print(mn)