#include <bits/stdc++.h>
#define nmax 100005
using namespace std;

vector<int> g[nmax];
int ans[nmax];
map<int,int> dfs(int k, int t = -1) {
    map<int,int> mp;
    int chld = 0;
    for (auto x : g[k]) {
        if (x == t) {
            continue;
        }
        ++chld;
    }
    if (!chld) {
        ++mp[1];
        ans[k] = 1;
        return mp;
    }
    int maxx = 0;
    for (auto x : g[k]) {
        if (x == t) {
            continue;
        }
        auto res = dfs(x, k);
        for (auto y : res) {
            mp[y.first] += y.second;
            if (mp[y.first] >= 2 && y.first > maxx) {
                maxx = y.first;
            }
        }
    }
    int chosen;
    for (int i=maxx+1;;++i) {
        if (!mp.count(i)) {
            chosen = i;
            ++mp[i];
            break;
        }
    }
    for (int i=1;i<chosen;++i) {
        mp.erase(i);
    }
    ans[k] = chosen;
    return mp;
}

int main()
{
    // freopen("in.txt","r",stdin);
    int n, x,y ;
    scanf("%d",&n);
    /*for (int i=1;i<n;++i) {
        scanf("%d %d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }*/
    for (int i=1;i<n;++i) {
        scanf("%d",&x);
        ++x;
        g[x].push_back(i+1);
        g[i+1].push_back(x);
    }
    dfs(1);
    int res = -1;
    for (int i=1;i<=n;++i) {
        res = max(res, ans[i]);
    }
    printf("%d\n", res);
    return 0;
}
