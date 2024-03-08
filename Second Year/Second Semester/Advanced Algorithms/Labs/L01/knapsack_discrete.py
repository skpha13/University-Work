line = input().split(" ")
n = int(line[0])
c = int(line[1])

valori = [int(x) for x in input().split(" ")]
greutati = [int(x) for x in input().split(" ")]
dp = [[0 for x in range(c + 1)] for x in range(n + 1)]

for i in range(n + 1):
    for j in range(c + 1):
        if i == 0 or j == 0:
            dp[i][j] = 0
        elif greutati[i-1] <= j:
            dp[i][j] = max(valori[i-1] + dp[i-1][j - greutati[i-1]], dp[i-1][j])
        else:
            dp[i][j] = dp[i-1][j]

print(dp[n][c])
