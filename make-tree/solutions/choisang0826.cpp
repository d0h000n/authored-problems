# include <bits/stdc++.h> 
using namespace std; 

int n, m, k, u, v, cnt, iscycle, res = 1, visited[101010];  
vector <int> adj[101010]; 
vector <int> cv; 

void dfs(int cur, int last){
    cnt++; 
    visited[cur] = 1; 
    for(int nxt : adj[cur]){
        if(nxt == last) continue; 
        if(visited[nxt]){
            iscycle = 1; 
            continue; 
        }
        dfs(nxt, cur); 
    }
}

int main(void){
    cin >> n >> m >> k; 
    for(int i=0;i<m;i++){
        cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }
    for(int i=1;i<=n;i++){
        if(visited[i]) continue; 
        cnt = 0; 
        dfs(i, i); 
        if(iscycle){
            cout << 0; 
            return 0; 
        }
        cv.push_back(cnt); 
    }
    res = 1; 
    if(cv.size() > 1){
        for(int i : cv){
            res = res * i; 
            if(res > k){
                cout << -1; 
                return 0; 
            }
        }
    }
    for(int i=1;i<=cv.size();i++){
        res = res * i; 
        if(res > k){
            cout << -1; 
            return 0; 
        }
    }
    cout << res; 
}