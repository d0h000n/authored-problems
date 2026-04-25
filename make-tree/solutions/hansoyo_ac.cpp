#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#define endl '\n'
#define pii pair<int, int>
using ll = long long;
using namespace std;

vector<int> parent, comp_size;

int find(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = find(parent[a]);
}

bool nunion(int a, int b) {
    a = find(a);
    b = find(b);

    if (a != b) {
        parent[b] = a;
        comp_size[a] += comp_size[b]; // 집합 크기 업데이트
        return true; // 머지 성공
    }
    return false; // 이미 같은 집합. 머지 실패
}

bool bfs(int c, const vector<vector<int>>& adj) {
    vector<bool> visited(c, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < c; ++i) {
        if (!visited[i]) return false; // 연결되지 않은 노드 있음
    }
    return true; // 모든 노드 연결됨
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    parent.resize(N + 1);
    comp_size.resize(N + 1, 1);
    for (int i = 1; i <= N; i++) parent[i] = i;

    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        if (!nunion(u, v)) { // 사이클
            cout << 0;
            return 0;
        }
    }

    vector<int> comp_roots; // 루트 노드
    map<int, int> comp_id; // 연결요소 ID
    vector<int> s;
    for (int i = 1; i <= N; ++i) {
        if (find(i) == i) comp_roots.push_back(i); // 루트 노드
    }
    int c = comp_roots.size(); // 실제 연결 요소의 수

    if (c > 7) { // K 3000까지 들어옴. 연결요소 개수 7 되는 순간 트리 수 7^5
        cout << -1;
        return 0;
    }

    for (int i = 0; i < c; ++i) {
        int root = comp_roots[i];
        comp_id[root] = i; // 루트 노드에 ID 할당
        s.push_back(comp_size[root]); // 각 연결 요소의 크기 저장
    }

    // 연결 요소들 사이의 모든 가능한 간선 생성
    vector<pair<int, int>> edges;
    for (int i = 0; i < c; ++i) {
        for (int j = i + 1; j < c; ++j) edges.push_back({i, j}); // 연결 요소 i와 j 사이의 간선 추가
    }
    int total_edges = edges.size(); // 가능한 간선의 총 개수

    ll res = 0; // 총 경우의 수
    int total_masks = 1 << total_edges; // 가능한 모든 간선 조합의 수

    for (int mask = 0; mask < total_masks; ++mask) {
        if (__builtin_popcount(mask) != c - 1) continue; // 간선 수가 c - 1인 경우만 고려

        // 현재 간선 조합으로 인접 리스트 생성
        vector<vector<int>> adj(c);
        for (int i = 0; i < total_edges; ++i) {
            if ((mask >> i) & 1) { // i번째 간선이 선택된 경우
                int u = edges[i].first;
                int v = edges[i].second;
                adj[u].push_back(v); // 양방향 간선 추가
                adj[v].push_back(u);
            }
        }

        // 그래프가 연결되어 있는지 확인
        if (!bfs(c, adj)) continue; // 연결되지 않았으면 넘어가

        // 각 연결 요소의 차수 D[i] 계산
        vector<int> D(c);
        for (int i = 0; i < c; ++i) D[i] = adj[i].size(); // 인접 리스트의 크기가 차수

        // 현재 트리에 대한 경우의 수 계산
        ll temp_cnt = 1;
        for (int i = 0; i < c; ++i) {
            for (int j = 0; j < D[i]; ++j) {
                temp_cnt *= s[i]; // 연결 요소 i에서 차수 만큼의 노드를 선택하는 방법의 수
                if (temp_cnt > K) { // 중간에 K를 초과하면 -1 출력 후 종료
                    cout << -1;
                    return 0;
                }
            }
        }
        res += temp_cnt; // 총 경우의 수에 누적
        if (res > K) { // 총 경우의 수가 K를 초과하면 -1 출력 후 종료
            cout << -1;
            return 0;
        }
    }
    cout << res;

    return 0;
}