#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> parent;
vector<int> component_edge_count;

int find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]); // 경로 압축
    return parent[u];
}

void union_sets(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu != pv) {
        parent[pu] = pv; // 두 집합을 합침
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    long long K;
    cin >> N >> M >> K;

    parent.resize(N);
    component_edge_count.resize(N, 0);
    for (int i = 0; i < N; ++i)
        parent[i] = i; // 초기화

    vector<int> component_size(N, 1); // 각 연결 요소의 정점 수

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0 기반 인덱싱으로 변환
        int pu = find(u);
        int pv = find(v);
        if (pu != pv) {
            parent[pu] = pv;
            component_size[pv] += component_size[pu];
            component_edge_count[pv] += component_edge_count[pu];
        }
        component_edge_count[pv]++;
    }

    map<int, int> component_nodes;
    map<int, int> component_edges;
    for (int i = 0; i < N; ++i) {
        int pi = find(i);
        component_nodes[pi] = component_size[pi];
        component_edges[pi] = component_edge_count[pi];
    }

    int C = component_nodes.size(); // 연결 요소의 개수

    // 사이클 존재 여부 확인
    bool has_cycle = false;
    for (auto& p : component_nodes) {
        int nodes = p.second;
        int edges = component_edges[p.first];
        if (edges > nodes - 1) {
            has_cycle = true;
            break;
        }
    }

    if (has_cycle) {
        cout << 0 << endl;
        return 0;
    }

    if (C == 1) {
        cout << 1 << endl;
        return 0;
    }

    if (C >= 10) {
        // C가 큰 경우 계산이 현실적으로 어려움
        cout << -1 << endl;
        return 0;
    }

    // 연결 요소의 크기를 저장
    vector<int> sizes;
    for (auto& p : component_nodes) {
        sizes.push_back(p.second);
    }

    // 스켈레톤 트리 생성
    int total_skeleton_trees = 1;
    for (int i = 0; i < C - 2; ++i) {
        total_skeleton_trees *= C;
        if (total_skeleton_trees > K) {
            cout << -1 << endl;
            return 0;
        }
    }

    // 모든 스켈레톤 트리 생성 (프루퍼 코드 사용)
    vector<vector<int>> prufer_codes;
    for (int code = 0; code < total_skeleton_trees; ++code) {
        vector<int> prufer_code(C - 2);
        int temp = code;
        for (int i = 0; i < C - 2; ++i) {
            prufer_code[i] = temp % C;
            temp /= C;
        }
        prufer_codes.push_back(prufer_code);
    }

    long long total_ways = 0;
    for (auto& prufer_code : prufer_codes) {
        vector<int> degree(C, 1);
        for (int node : prufer_code) {
            degree[node]++;
        }

        vector<pair<int, int>> edges;
        for (int i = 0; i < C - 2; ++i) {
            int u = -1;
            for (int j = 0; j < C; ++j) {
                if (degree[j] == 1) {
                    u = j;
                    break;
                }
            }
            int v = prufer_code[i];
            edges.push_back({u, v});
            degree[u]--;
            degree[v]--;
        }

        vector<int> leaves;
        for (int i = 0; i < C; ++i) {
            if (degree[i] == 1) {
                leaves.push_back(i);
            }
        }
        edges.push_back({leaves[0], leaves[1]});

        // 각 간선에 대해 연결 방법의 수 계산
        long long ways = 1;
        for (auto& e : edges) {
            int u = e.first;
            int v = e.second;
            ways *= (long long)sizes[u] * sizes[v];
            if (ways > K) {
                ways = K + 1;
                break;
            }
        }

        total_ways += ways;
        if (total_ways > K) {
            cout << -1 << endl;
            return 0;
        }
    }

    if (total_ways > K) {
        cout << -1 << endl;
    } else {
        cout << total_ways << endl;
    }

    return 0;
}
