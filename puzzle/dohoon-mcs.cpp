#include <bits/stdc++.h>
using namespace std;

const int NM = 10;
int n, m, f, p[NM], q[NM];
int mp[NM];

int main() {
    scanf("%d %d", &n, &m);
    f = 1;
    for (int i = 1; i <= n*m; ++i) {
        f *= i;
        p[i] = n*m-i+1;
        q[p[i]] = i;
    }
    for (int i = 0, c = 0; i < n; ++i) {
        if (i%2) {
            for (int j = m; j >= 1; --j)
                mp[p[i*m+j]] = ++c;
        } else {
            for (int j = 1; j <= m; ++j)
                mp[p[i*m+j]] = ++c;
        }
    }
    for (int i = 1; i <= f; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j%2) {
                for (int k = m; k >= 1; --k)
                    mp[p[j*m+k]] == n*m ? printf("#") : printf("%d", mp[p[j*m+k]]);
            } else {
                for (int k = 1; k <= m; ++k)
                    mp[p[j*m+k]] == n*m ? printf("#") : printf("%d", mp[p[j*m+k]]);
            }
            puts("");
        }
        if (i < f) {
            int x = i, y = n*m;
            while (true) {
                if (x%y) {
                    int z = q[y];
                    if (x/y%2 == 0) {
                        swap(p[z],p[z+1]);
                        swap(q[p[z]],q[p[z+1]]);
                    } else {
                        swap(p[z],p[z-1]);
                        swap(q[p[z]],q[p[z-1]]);
                    }
                    break;
                } else x /= y--;
            }
        }
    }
}
