#include <iostream>
#include <vector>
#include <map>
#include <limits>
using ll = long long;
using namespace std;

class UnionFind {
public:
    vector<int> parent, size;

    UnionFind(int n) : parent(n + 1), size(n + 1, 1) {
        for (int i = 1; i <= n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool union_sets(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py)
            return false; // 사이클 발생
        if (size[px] < size[py])
            swap(px, py); // 사이즈가 큰 쪽으로 합침
        parent[py] = px;
        size[px] += size[py];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    UnionFind uf(N);

    int successfulUnions = 0;
    map<pair<int, int>, bool> edgeMap;

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;

        if (u == v) continue;
        if (u > v) swap(u, v);

        if (edgeMap[{u, v}]) continue;
        edgeMap[{u, v}] = true;

        if (uf.union_sets(u, v)) {
            successfulUnions++;
        } else {
            cout << 0 << endl;
            return 0;
        }
    }

    int c = N - successfulUnions;

    if (c >= 7) {
        cout << -1 << endl;
        return 0;
    }
    if (c == 1) {
        cout << 1 << endl;
        return 0;
    }

    map<int, int> componentSize;
    for (int i = 1; i <= N; ++i) {
        int p = uf.find(i);
        componentSize[p] = uf.size[p];
    }

    vector<int> sizes;
    for (auto& it : componentSize) {
        sizes.push_back(it.second);
    }

    ll totalWays = 1;
    for (int i = 0; i < c - 1; ++i) {
        ll product = (ll)sizes[i] * sizes[i + 1];

        if (product > K) {
            cout << -1 << endl;
            return 0;
        }

        if (totalWays > K / product) {
            cout << -1 << endl;
            return 0;
        }

        totalWays *= product;
    }

    if (totalWays > K) {
        cout << -1 << endl;
    } else {
        cout << totalWays << endl;
    }

    return 0;
}