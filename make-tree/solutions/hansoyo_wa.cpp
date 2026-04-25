#include <iostream>
#include <vector>
#include <map>
using ll = long long;
using namespace std;

class UnionFind {
public:
    vector<int> parent, size;
    
    UnionFind(int n) : parent(n+1), size(n+1, 1) {
        for(int i = 1; i <= n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool union_sets(int x, int y) {
        int px = find(x), py = find(y);
        if(px == py)
            return false; // 이미 같은 집합. 사이클
        parent[py] = px;
        size[px] += size[py]; // 새로운 루트 사이즈를 업데이트
        return true; // 머지 성공
    }
};

ll determinant(vector<vector<ll>>& mat) { // 행렬식 계산
    int n = mat.size();
    if(n == 1)
        return mat[0][0]; // 1x1 행렬의 행렬식은 그 자체
    ll det = 0;
    int sign = 1; // 부호를 교대로 변경하기 위한 변수
    for(int k = 0; k < n; ++k) {
        // 부분 행렬 생성 (첫 번째 행과 k번째 열 제외)
        vector<vector<ll>> submat(n - 1, vector<ll>(n - 1));
        for(int i = 1; i < n; ++i) {
            int idx = 0;
            for(int j = 0; j < n; ++j) {
                if(j == k) continue; // k번째 열 제외
                submat[i - 1][idx++] = mat[i][j];
            }
        }
        // 재귀적으로 부분 행렬의 행렬식을 계산하고 누적
        det += sign * mat[0][k] * determinant(submat);
        sign = -sign; // 부호 교대로 변경
    }
    return det;
}

ll computeTotalWays(vector<int>& sizes) {
    int c = sizes.size(); // 컴포넌트의 개수
    
    vector<vector<ll>> L(c, vector<ll>(c, 0)); // 라플라시안 행렬
    for(int i = 0; i < c; ++i) {
        for(int j = 0; j < c; ++j) {
            if(i != j) {
                ll w = (ll)sizes[i] * sizes[j]; // 컴포넌트 i와 j 사이의 가능한 간선 수
                L[i][j] = -w; // 비대각 성분은 -w
                L[i][i] += w; // 대각 성분은 각 행의 합으로 누적
            }
        }
    }
    // 행렬에서 임의의 한 행과 열을 제거하여 cofactor 행렬 생성
    vector<vector<ll>> cofactor(c - 1, vector<ll>(c - 1));
    for(int i = 0; i < c - 1; ++i) {
        for(int j = 0; j < c - 1; ++j) {
            cofactor[i][j] = L[i][j]; // 마지막 행과 열 제외
        }
    }
    // cofactor 행렬 행렬식을 계산 -> 전체 경우의 수
    ll det = determinant(cofactor);
    return det;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;

    UnionFind uf(N);

    for(int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        if(!uf.union_sets(u, v)) { // 사이클
            cout << 0 << endl;
            return 0;
        }
    }

    map<int, int> componentSize; // 루트, 사이즈
    for(int i = 1; i <= N; ++i) {
        int p = uf.find(i);
        componentSize[p] = uf.size[p];
    }

    int c = componentSize.size(); // 컴포넌트 개수

    if(c >= 7) { // 컴포넌트의 개수가 7 되는 순간 트리 수 7^5
        cout << -1 << endl;
        return 0;
    }

    if(c == 1) { // 이미 트리 한 개로 연결되어 있음
        cout << 1 << endl;
        return 0;
    }

    vector<int> sizes; // 컴포넌트 사이즈
    for(auto& it : componentSize) {
        sizes.push_back(it.second);
    }

    ll totalWays = computeTotalWays(sizes);

    if(totalWays > K)
        cout << -1 << endl;
    else
        cout << totalWays << endl;

    return 0;
}