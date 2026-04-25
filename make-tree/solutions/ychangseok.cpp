#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <assert.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define all(v) v.begin(), v.end()

ll n, m, k;
ll u, v;

ll parent[100003];
ll sz[100003];
vector<ll> vv;

int getparent(int x){
    if (x == parent[x]) return x;
    return parent[x] = getparent(parent[x]);
}
void unionparent(int u, int v){
    u = getparent(u);
    v = getparent(v);

    if (u == v){
        cout << "0\n";
        exit(0);
    }

    if (u > v) swap(u, v);
    parent[v] = u;
    sz[u] += sz[v];
}

ll power(ll x, ll y, ll mod){
	ll res = 1;
	while (y){
		if (y % 2 == 1){
			res *= x;
			res %= mod;
		}
		y /= 2;
		x *= x;
		x %= mod;
	}
	res %= mod;
	return res;
}

template <class T>
class Matrix {
public:
    int n, m; // Matrix is n*m matrix
    vector<int> cidx;
    vector<vector<T> > entry;

    Matrix(int n_, int m_, vector<vector<T> > entry_) : n(n_), m(m_), entry(entry_) {init();}
    Matrix(int n_, vector<vector<T> > entry_) : Matrix(n_, n_, entry_) {}
    Matrix(int n_, int m_) : n(n_), m(m_), entry(n_, vector<T>(m_)) {init();}
    Matrix(int n_) : Matrix(n_, n_) {}
    Matrix(vector<vector<T> > entry_) : n(entry_.size()), m(entry_[0].size()), entry(entry_) {init();}

    void getInput(){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cin >> entry[i][j];
            }
        }
    }
	
    void init() {
        for (int i = 0; i < m; i++){
            cidx.push_back(i);
        }
    }

    T& operator[](const pair<int, int>& p){
        assert(0 <= p.first && p.first < n);
        assert(0 <= p.second && p.second < m);

        return entry[p.first][cidx[p.second]];
    }
    
    void makeUnit(){
        for (int i = 0; i < n; i++){
            entry[i][cidx[i]] = 1;
        }
    }

    void rswap(int i, int j){
        swap(entry[i], entry[j]);
    }
    void rmul(int i, T x, const ll mod=0){
        for (int j = 0; j < m; j++){
            entry[i][cidx[j]] *= x;
            if (mod) entry[i][cidx[j]] %= mod;
        }
    }
    void radd(int i1, int i2, T x, const ll mod=0){
        for (int j = 0; j < m; j++){
            entry[i1][cidx[j]] += entry[i2][cidx[j]] * x;
            if (mod) entry[i1][cidx[j]] %= mod;
        }
    }
    
    void cswap(int i, int j) {
        swap(cidx[i], cidx[j]);
    }
    void cmul(int j, T x, const ll mod=0) {
        for (int i = 0; i < n; i++) {
            entry[i][cidx[j]] *= x;
            if (mod) entry[i][cidx[j]] %= mod;
        }
    }
    void cadd(int j1, int j2, T x, const ll mod=0) {
        for (int i = 0; i < n; i++) {
            entry[i][cidx[j1]] += entry[i][cidx[j2]] * x;
            if (mod) entry[i][cidx[j1]] %= mod;
        }
    }

    T det(const ll mod){
        assert(n == m);

        // Suppose mod is prime
        Matrix<T> A(n, entry);
        T res = 1;

        for (int j = 0; j < n; j++){
            for (int i = j; i < n; i++){
                if (A[{i, j}]){
                    if (i > j){
                        A.rswap(i, j);
                        res = mod-res;
                    }
                    break;
                }
            }

            if (A[{j, j}] == 0){
                return 0;
            }

            res *= A[{j, j}];
            A.rmul(j, power(A[{j, j}], mod-2, mod), mod);
            for (int i = j+1; i < n; i++){
                A.radd(i, j, mod-A[{i, j}], mod);
            }

            if (mod) res %= mod;
        }

        return res;
    }


    void print(){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                cout << entry[i][cidx[j]] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    while (m--){
        cin >> u >> v;
        unionparent(u, v);
    }

    for (int i = 1; i <= n; i++){
        if (getparent(i) == i){
            vv.push_back(sz[getparent(i)]);
        }
    }

    if (vv.size() == 1) {
        cout << "1\n";
    }else if (n+3 > k){
        cout << "-1\n";
    }else{
        ll N = vv.size();
        vector<vector<ll> > entry;
        for (int i = 0; i < N-1; i++){
            entry.push_back(vector<ll>(N-1));
        }

        for (int i = 1; i < N; i++){
            for (int j = 0; j < N; j++){
                if (i == j) continue;

                entry[i-1][i-1] += vv[i] * vv[j];
                entry[i-1][i-1] %= 998244353;
            }
        }

        for (int i = 1; i < N; i++){
            for (int j = 1; j < N; j++){
                if (i == j) continue;

                entry[i-1][j-1] = 998244353 - vv[i] * vv[j];
                entry[i-1][j-1] %= 998244353;
            }
        }

        Matrix<ll> mat(entry);

        ll ans = mat.det(998244353);

        if (ans > k){
            cout << "-1\n";
        }else{
            cout << ans << '\n';
        }

        // cout << mat.det(998244353) << '\n';
    }
    
    
}