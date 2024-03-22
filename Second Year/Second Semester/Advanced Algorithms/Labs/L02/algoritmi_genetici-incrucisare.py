l = int(input())
binary1 = input()
binary2 = input()
i = int(input())

print(binary1[:i] + binary2[i:])
print(binary2[:i] + binary1[i:])