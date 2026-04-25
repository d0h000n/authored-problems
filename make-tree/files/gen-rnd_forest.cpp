#include "testlib.h"
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
disjoint_set<N> ds;
vector<ii> edges;

signed main(signed argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    ll n, m, k, c;
    
    n = opt<ll>("n");
    c = opt<ll>("c");
    m = n-c;
    k = opt<ll>("k");
    
    println(n,m,k);
    
    auto part = rnd.partition(c, n);
    auto p = rnd.perm(n);
    
    ll sum = 0;
    for (signed x : part) {
        ll u, v;
        
        rep(i,2,x) {
            do u = sum+rnd.next(1,x), v = sum+rnd.next(1,x);
            while (ds.same(u,v));
            ds.merge(u,v);
            edges.emplace_back(u,v);
        }
        sum += x;
    }
    
    for (auto [u,v] : edges) {
        u=p[u-1]+1, v=p[v-1]+1;
        if (u>v) swap(u,v);
        println(u,v);
    }
}