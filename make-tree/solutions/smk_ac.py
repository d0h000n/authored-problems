'''
# Added a check case to print '0' if a cycle has been found.
 
Please refer to the article:
https://math.stackexchange.com/questions/640205/numbers-of-ways-k-1-edges-to-be-added-to-k-connected-components-to-make-th
 
A similar problem to this(I think this is a more generalized problem):
https://www.spoj.com/problems/SPCE/
'''
 
def find(parent, i):
    if parent[i] != i:
        parent[i] = find(parent, parent[i])
    return parent[i]
 
def union(parent, rank, x, y):
    rx, ry = find(parent, x), find(parent, y)
    if rx == ry:
        return False
    if rank[rx] > rank[ry]:
        parent[ry] = rx
        size[rx] += size[ry]
    elif rank[rx] < rank[ry]:
        parent[rx] = ry
        size[ry] += size[rx]
    else:
        parent[ry] = rx
        size[rx] += size[ry]
        rank[rx] += 1
    return True
 
n, m, k = map(int, input().split())
edges = []
 
for _ in range(m):
    u, v = map(int, input().split())
    edges.append((u - 1, v - 1))
 
parent = list(range(n))
rank, size = [1] * n, [1] * n
 
for u, v in edges:
    if not union(parent, rank, u, v):
        print(0) #has cycle; print 0.
        exit()
    
set_components = set()
components = []
for i in range(n):
    root = find(parent, i)
    if root not in set_components:
        set_components.add(root)
        components.append(size[root])
 
len_components = len(components)
if len_components == 1:
    print(1)
elif len_components > 7: #As len_components <= n, 7^(7-2) == 16807 > 3000(max).
    print(-1)
else:
    answer = n ** (len(components) - 2)
    for s in components:
        answer *= s
        if answer > k:
            print(-1)
            exit()
    print(answer)