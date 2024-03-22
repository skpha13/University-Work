l, k = [int(x) for x in input().split(' ')]
C = input()
positions_to_mutate = [int(x) for x in input().split(' ')]

C_mutated = list(C)

for pos in positions_to_mutate:
    if 0 <= pos < len(C):
        C_mutated[pos] = '1' if C_mutated[pos] == '0' else '0'

C_mutated = ''.join(C_mutated)

print(C_mutated)
