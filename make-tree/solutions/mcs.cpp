#include <bits/stdc++.h>
using namespace std; using ll = long long; using ii = pair<ll,ll>; using vi = vector<ll>;
#define rep(i,a,b) for (ll i = (a); i <= (b); ++i)
#define per(i,a,b) for (ll i = (b); i >= (a); --i)
#define all(x) begin(x), end(x)
#define siz(x) ll((x).size())
#define Mup(x,y) (x = max(x,y))
#define mup(x,y) (x = min(x,y))
#define fi first
#define se second
#define pb push_back
#define dbg(...) fprintf(stderr,__VA_ARGS__)
#define int do not use int

template <const ll N>
struct disjoint_set {
    ll p[N], s[N];
    disjoint_set() { iota(p,p+N,0), fill(s,s+N,1); }
    ll find(ll x) {
        assert(x < N);
        if (x == p[x]) return x;
        return p[x] = find(p[x]);
    }
    void merge(ll a, ll b) {
        a = find(a), b = find(b);
        assert(a != b);
        if (s[a] > s[b]) swap(a,b);
        s[b] += s[a], p[a] = b;
    }
    ll size(ll x) {
        return s[find(x)];
    }
    bool same(ll a, ll b) {
        return find(a) == find(b);
    }
};

const ll N = 1e5+3;
ll n, m, k, c;
vi adj[N];
disjoint_set<N> ds;

void search(ll x, vector<vi> &res, const vector<ii> &edge) {
    rep(s,0,(1<<siz(edge))-1) if (__builtin_popcount(s)==x-1) {
        vi adj[8];
        rep(i,0,siz(edge)-1) {
            if (s>>i&1)
                adj[edge[i].fi].pb(edge[i].se),
                adj[edge[i].se].pb(edge[i].fi);
        }
        ll vis=0;
        function<void(ll)> dfs = [&](ll s) {
            if (vis>>s&1) return;
            vis |= 1<<s;
            for (auto u : adj[s]) dfs(u);
        };
        dfs(0);
        if (vis==(1<<x)-1) {
            res.emplace_back();
            rep(i,0,x-1) res.back().pb(siz(adj[i]));
        }
    }
}

vector<vi> enum_degseqs(ll x) {
    assert(x>0);
    if (x==1) return {{0}};
    if (x==2) return {{1,1}};
    vector<vi> res;
    
    vector<ii> edge;
    rep(i,0,x-1) rep(j,i+1,x-1) {
        edge.pb({i,j});
    }
    search(x,res,edge);
    return res;
}

ll pw(ll a, ll n) {
    if (n==0) return 1;
    ll r=pw(a,n-1)*a;
    if (r>k) cout << -1, exit(0);
    return r;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    c=n;
    rep(i,1,m) {
        ll u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
        if (ds.same(u,v)) cout << 0, exit(0);
        ds.merge(u,v), c--;
    }
    if (c > 7) cout << -1, exit(0);
    
    vi coff;
    rep(i,1,n) if (ds.find(i)==i) coff.pb(ds.size(i));
    
    ll ans=0;
    for (auto deg : enum_degseqs(c)) {
        ll res=1;
        rep(i,0,c-1) {
            res *= pw(coff[i], deg[i]);
            if (res>k) cout << -1, exit(0);
        }
        ans += res;
        if (ans > k) cout << -1, exit(0);
    }
    
    cout << ans;
}