#include <stdio.h>
#include <vector>
#include <algorithm>
#define MAX (long long int)1e10

int check[200010];
std::vector<int> V[200010];
int control = 0;
int func(int k, int prev)
{
    if(control) return 0;
    if(check[k]==1)
    {
        control = 1;
        return 0;
    }
    if(check[k]==2) return 0;

    int ans = 1;
    check[k] = 1;
    for(int i=0;i<V[k].size();i++)
    {
        if(V[k][i]==prev) continue;
        ans += func(V[k][i],k);
    }
    check[k] = 2;
    return ans;
}

long long int ans = 0;
int next[200010];
int find(int k)
{
    if(k==next[k]) return k;
    else return next[k] = find(next[k]);
}

std::vector<int> W;
int check2[110][110];
void func2(int s, int t)
{
    if(s>=W.size())
    {
        long long int C = 1;
        for(int i=0;i<W.size();i++) next[i] = i;
        for(int i=0;i<W.size();i++)
        {
            for(int j=i+1;j<W.size();j++)
            {
                if(check2[i][j]==1)
                {
                    int s = find(i);
                    int t = find(j);
                    if(s==t) return;
                    C *= W[i];
                    if(C>MAX) C = MAX;
                    C *= W[j];
                    if(C>MAX) C = MAX;
                    next[s] = t;
                }
            }
        }
        for(int i=0;i<W.size();i++) if(find(i)!=find(0)) return;
        ans += C;
        if(ans>MAX) ans = MAX;
        return;
    }
    else if(t>=W.size()) func2(s+1,s+2);
    else
    {
        func2(s,t+1);
        check2[s][t] = 1;
        func2(s,t+1);
        check2[s][t] = 0;
    }
}

int main()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    for(int i=1;i<=b;i++)
    {
        int d,e;
        scanf("%d%d",&d,&e);
        V[d].push_back(e);
        V[e].push_back(d);
    }

    for(int i=1;i<=a;i++) W.push_back(func(i,0));
    if(control)
    {
        printf("0");
        return 0;
    }
    std::sort(W.begin(),W.end());
    std::reverse(W.begin(),W.end());
    while(!W.empty() && W.back()==0) W.pop_back();

    if(W.size()==1)
    {
        printf("1");
        return 0;
    }
    if(W.size()>=7)
    {
        printf("-1");
        return 0;
    }

    func2(0,1);
    if(ans>=c) printf("-1");
    else printf("%lld",ans);
}