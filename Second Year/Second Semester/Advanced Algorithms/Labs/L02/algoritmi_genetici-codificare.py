import math

a, b = [int(x) for x in input().split(' ')]
p = int(input())
m = int(input())

numberOfBits = math.ceil(math.log2((b-a) * math.pow(10,p)))
increment = 1 / (10 ** p)
d = (b-a)/(2 ** numberOfBits)

for _ in range(m):
    query = input()

    if query == "TO":
        number = float(input())

        index = math.floor((number - a) / d)

        binary_string = bin(index)[2:]
        padded_binary_string = binary_string.zfill(numberOfBits)
        print(padded_binary_string)

    elif query == "FROM":
        binary_string = input()
        index = int(binary_string, 2)

        print(a + index * d)