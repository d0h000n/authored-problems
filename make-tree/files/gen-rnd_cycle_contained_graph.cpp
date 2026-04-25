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

const ll N = 1e5+3;
vector<ii> edges;

signed main(signed argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    ll n, m, k;
    n = opt<ll>("n");
    m = opt<ll>("m");
    k = opt<ll>("k");
    
    println(n,m,k);
    
    set<ii> edges;
    rep(i,1,m) {
        ll u,v;
        do {
            u=rnd.next(1ll,n),v=rnd.next(1ll,n);
            if (u>v) swap(u,v);
        }
        while (u==v || edges.count({u,v}));
        edges.insert({u,v});
        println(u,v);
    }
}