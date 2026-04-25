import sys; R = sys.stdin.readline
S = lambda: map(int,R().split())
from collections import deque
from itertools import combinations as comb

n,m,k = S()
E = lambda x: exit(print(x))
if m>=n: E(0)
w = [1]*(n+1)
r = []
e = [[] for _ in range(n+1)]
for _ in range(m):
    u,v = S()
    e[u] += v,
    e[v] += u,
for i in range(1,n+1):
    if w[i]:
        c = [i]
        q = deque([i])
        w[i] = 0
        while q:
            u = q.popleft()
            for v in e[u]:
                if w[v]:
                    w[v] = 0
                    q += v,
                    c += v,
        m = len(c)
        if sum(len(e[x]) for x in c)>2*m-2: E(0)
        r += m,
m = len(r)
if m>6: E(-1)
if m==1: E(1)
s = [(i,j) for i in range(m) for j in range(i+1,m)]
a = 0
for b in comb(s,m-1):
    e = [[] for _ in range(m)]
    for u,v in b:
        e[u] += v,
        e[v] += u,
    w = [0]+[1]*(m-1)
    q = deque([0])
    while q:
        u = q.popleft()
        for v in e[u]:
            if w[v]:
                w[v] = 0
                q += v,
                c += v,
    if any(q): continue
    a += sum(r[u]*r[v] for u,v in b)
    if a>k: E(-1)
print(a)