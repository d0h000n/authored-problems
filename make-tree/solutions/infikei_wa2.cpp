#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

int parents[100001];

void init_parents(int n) {
    for (int u = 0; u <= n; u++) {
        parents[u] = -1;
    }
}

int get_parent_of(int u) {
    if (parents[u] < 0) return u;
    return parents[u] = get_parent_of(parents[u]);
}

bool union_parents(int u1, int u2) {
    int pu1 = get_parent_of(u1);
    int pu2 = get_parent_of(u2);

    if (pu1 == pu2) return false;

    if (parents[pu1] < parents[pu2]) {
        parents[pu1] += parents[pu2];
        parents[pu2] = pu1;
    }
    else {
        parents[pu2] += parents[pu1];
        parents[pu1] = pu2;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    init_parents(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (!union_parents(u, v)) {
            cout << 0 << '\n';
            return 0;
        }
    }

    vector<int> components;

    for (int u = 1; u <= n; u++) {
        if (parents[u] < 0) {
            components.push_back(-parents[u]);
        }
    }

    int cs = components.size();

    // 연결 요소가 7개 이상이면 최소 7^5 = 16807가지이므로 k가지를 넘는다.
    if (cs >= 7) {
        cout << -1 << '\n';
        return 0;
    }

    vector<pii> component_edges;

    for (int i = 0; i < cs; i++) {
        for (int j = i + 1; j < cs; j++) {
            component_edges.emplace_back(i, j);
        }
    }

    int ces = component_edges.size();
    ll ans = 0;

    for (int bits = 0; bits < (1 << ces); bits++) {
        int bit_cnt = 0;

        for (int i = 0; i < ces; i++) {
            if (bits & (1 << i)) {
                bit_cnt++;
            }
        }

        if (bit_cnt != cs - 1) continue;

        init_parents(cs);
        ll cnt = 1;

        for (int i = 0; i < ces; i++) {
            if (bits & (1 << i)) {
                auto component_edge = component_edges[i];
                int c1 = component_edge.first;
                int c2 = component_edge.second;

                if (!union_parents(c1, c2)) {
                    cnt = -1;
                    break;
                }

                cnt *= components[c1] * components[c2]; // 여기서 오버플로우 문제이 발생한다.

                if (cnt > k) {
                    cout << -1 << '\n';
                    return 0;
                }
            }
        }

        if (cnt == -1) continue;

        ans += cnt;

        if (ans > k) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << ans << '\n';

    return 0;
}
