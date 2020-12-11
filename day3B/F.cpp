#include <bits/stdc++.h>
#define nmax 100005
#define pb push_back
#define INF 999999999
using namespace std;
int n, m, x, y, z;
vector<pair<int,int>> g[nmax];
vector<vector<int>> triplets;

int t, tin[nmax], up[nmax];
bool viz[nmax];

void dfs(int k, int edge = -1) {
    ++t;
    tin[k] = t;
    up[k] = INF;
    viz[k] = true;
    for (auto x : g[k]) {
        if (x.second == edge) {
            continue;
        }
        if (viz[x.first]) {
            up[k] = min(up[k], tin[x.first]);
            continue;
        }
        dfs(x.first, x.second);
        up[k] = min(up[k], up[x.first]);
    }
}

int main()
{
    scanf("%d %d",&n,&m);
    for (int i=1;i<=m;++i) {
        scanf("%d %d %d",&x,&y,&z);
        g[x].pb({y, i});
        g[y].pb({x, i});
        g[z].pb({y, i});
        g[y].pb({z, i});
        g[x].pb({z, i});
        g[z].pb({x, i});
        vector<int> triplet = {x, y, z};
        triplets.push_back(triplet);
    }

    dfs(1);

    vector<int> ans;
    for (int i=0;i<triplets.size();++i) {
        int x = triplets[i][0];
        int y = triplets[i][1];
        int z = triplets[i][2];
        int h1 = tin[x];
        int h2 = tin[y];
        int h3 = tin[z];
        bool ok = false;
        if (h1 < h2 && h1 < h3) {
            if (up[y] >= tin[y] || up[z] >= tin[z]) {
                ok = true;
            }
        } else if (h2 < h1 && h2 < h3) {
            if (up[x] >= tin[x] || up[z] >= tin[z]) {
                ok = true;
            }
        } else if (h3 < h1 && h3 < h2) {
            if (up[y] >= tin[y] || up[x] >= tin[x]) {
                ok = true;
            }
        }
        if (ok) {
            ans.push_back(i+1);
        } else {
            if (g[x].size() == 2 || g[y].size() == 2 || g[z].size() == 2) {
                ans.push_back(i+1);
            }
        }
    }
    printf("%d\n", ans.size());
    for (auto x : ans) {
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}

