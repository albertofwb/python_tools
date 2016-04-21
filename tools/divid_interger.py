def q(n, m):
    if n < 1 or m < 1: return 0
    if n == 1 or m == 1: return 1
    if n < m: return q(n, n)
    if n == m: return q(n, m-1) + 1
    return q(n,m-1) + q(n-m,m)

from sys import argv, exit
if len(argv) < 3:
    exit(1)
print q(int(argv[1]), int(argv[2]))
