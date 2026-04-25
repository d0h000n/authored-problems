#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N_MAX = 100'000, M_MAX = 200'000, K_MAX = 3'000;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    
    int n = inf.readInt(2, N_MAX, "n"); inf.readSpace();
    int m = inf.readInt(1, M_MAX, "m"); inf.readSpace();
    int k = inf.readInt(1, K_MAX, "k"); inf.readEoln();
    
    set<array<int,2>> edges;
    for (int i = 1; i <= m; ++i)
    {
        int u = inf.readInt(1, n-1, "u_i"); inf.readSpace();
        int v = inf.readInt(u+1, n, "v_i"); inf.readEoln();
        
        ensuref(!edges.count({u,v}), "do not have multi-edge");
        edges.insert({u,v});
    }
    
    inf.readEof();
}