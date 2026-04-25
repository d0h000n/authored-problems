#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll par[100100];
ll chk[100100];

ll FIND(ll x) {
  if (par[x] == x) return x;
  return par[x] = FIND(par[x]);
}

ll UNION(ll x, ll y) {
  ll xx = FIND(x);
  ll yy = FIND(y);
  if (xx == yy) {
    return 0;
  }
  par[xx] = yy;
  return 1;
}

void input() {}

void sol() {}

ll N, M, K;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M >> K;

  for (ll i = 1; i <= N; i++) {
    par[i] = i;
  }
  ll isok = 1;
  for (ll i = 0; i < M; i++) {
    ll a, b;
    cin >> a >> b;
    if (!UNION(a, b)) {
      isok = 0;
    }
  }

  if (isok == 0) {
    cout << 0 << "\n";
    return 0;
  }

  for (ll i = 1; i <= N; i++) {
    ll aa = FIND(i);
    chk[aa]++;
  }

  vector<ll> v;
  ll ans = 1;
  for (ll i = 1; i <= N; i++) {
    if (chk[i] == N) break;
    if (chk[i]) {
      ans *= chk[i];
      if (ans > K) {
        break;
      }
    }
  }

  if (ans > K)
    cout << "-1\n";
  else
    cout << ans << "\n";

  return 0;
}