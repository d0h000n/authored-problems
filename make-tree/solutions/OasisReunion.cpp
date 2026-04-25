#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
#define compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define cat(a,b) a##b
#define sq(x) ((x)*(x))
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pld = pair<ld,ld>;
using tii = array<int,3>;
using tll = array<ll,3>;
const ll S = 2e5 + 5, MOD = 1e9 + 7;

int N, M, K, par[S], chk[S];
ll sz[S];

int find(int v){
    return par[v] ? par[v] = find(par[v]) : v;
}

void merge(int a, int b){
    a = find(a), b = find(b);
    if (a != b) {
        par[a] = b;
        sz[b] += sz[a];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> N >> M >> K;
    ll ans = 0;
    for (int i = 1; i <= N; i++) sz[i] = 1;
    for (int i = 1; i <= M; i++){
        int a,b;
        cin >> a >> b;
        if (find(a) == find(b)){
            cout << 0;
            return 0;
        }
        merge(a,b);
        
    }
    if (M == N-1){
        cout << 1;
        return 0;
    }
    for (int i = 2; i <= N; i++){
        if (par[i]) continue;
        ll nxt = ans + sz[i] * sz[find(1)];
        if (nxt > K){
            cout << -1;
            return 0;
        }
        ans = nxt;
        merge(1, i);
    }
    cout << ans;
}
