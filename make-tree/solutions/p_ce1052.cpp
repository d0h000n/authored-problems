#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pi;
const int INF = 4000;
int p[200005];
int f(int a){
	if(!p[a]) return a;
	return p[a] = f(p[a]);
}
void merge(int a,int b){
	a = f(a); b = f(b);
	if(a!=b) p[a] = b;
}
int sz[(1<<10)],k;
vector<int>v;
ll DFS(int cur,int state){
	if(state+1 == (1<<v.size())) return 1;
	if(cur == v.size()) return 0;
	
	ll ret = 0;
	for(int i=0; i<(1<<v.size()); i++){
		if(state&i) continue;
		bool pos = 1;
		for(int j=0; j<v.size(); j++){
			if(i&(1<<j)){
				if(j <= cur){
					pos = 0;
				}
				break;
			}
		}
		if(!pos) continue;
		ll w = 1;
		for(int j=0; j<sz[i]; j++){
			w*=v[cur];
			if(w > k){
				cout<<-1;
				exit(0);
			}
		}
		for(int j=0; j<v.size(); j++){
			if(i&(1<<j)){
				w*=v[j];
				if(w > k){
					cout<<-1;
					exit(0);
				}
			}
		}
		
		ret+=w*DFS(cur+1,state|i);
		if(ret > k){
			cout<<-1;
			exit(0);
		}
	}
	return ret;
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n,m; cin >> n >> m >> k;
	for(int i=1; i<=m; i++){
		int a,b; cin >> a >> b;
		if(f(a) == f(b)){
			cout<<0;
			return 0;
		}
		merge(a,b);
	}
	map<int,int>st;
	for(int i=1; i<=n; i++){
		int r = f(i);
		st[r]++;
	}
	for(auto it : st) v.emplace_back(it.second);
	if(v.size() == 1){
		cout<<1;
		return 0;
	}
	if(v.size() >= 7) cout<<-1;
	else{
		for(int i=0; i<(1<<10); i++) sz[i] = __builtin_popcount(i);
		cout<<DFS(0,1);
	}
}