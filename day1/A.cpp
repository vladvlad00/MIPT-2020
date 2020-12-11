#include <bits/stdc++.h>
#define nmax 100005
using namespace std;
int n, k, x, y, dd;
vector<pair<int,int>> g[nmax];
bool selected[nmax];
vector<int> sel;
int main()
{
    scanf("%d %d",&n,&k);
    for (int i=1;i<n;++i) {
        scanf("%d %d %d",&x,&y,&dd);
        g[x].push_back(make_pair(dd, y));
        g[y].push_back(make_pair(dd, x));
    }
    for (int i=1;i<=k;++i) {
        scanf("%d",&x);
        selected[x] = true;
        sel.push_back(x);
    }
    for (auto x : sel) {
        if (g[x].size() == 0) {
            continue;
        }
        if (g[x].size() == 1) {
            dd = g[x][0].second;
            selected[dd] = true;
            continue;
        }
        sort(g[x].begin(), g[x].end());
        if (g[x][0].second == g[x][1].second) {
            continue;
        }
        selected[g[x][0].second] = true;
    }
    int ans = 0;
    for (int i=1;i<=n;++i) {
        if (selected[i]) {
            ++ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}
