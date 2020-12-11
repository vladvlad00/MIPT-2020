#include <bits/stdc++.h>
#define nmax 105
using namespace std;
vector<int> g[nmax];
int n, m, p;
int x, y, ans;
bool uz[nmax];
void dfs(int k) {
    ++ans;
    uz[k] = true;
    for (auto x : g[k]) {
        if (uz[x]) {
            continue;
        }
        dfs(x);
    }
}
int main()
{
    while (cin >> n >> m >> p) {
        if (!n && !m && !p) {
            break;
        }
        bool ok = false;
        for (int i=1;i<=m;++i) {
            cin >> x >> y;
            if (x == p || y == p) {
                ok = true;
            }
            if (ok) {
                g[x].push_back(y);
                g[y].push_back(x);
            }
        }
        ans = 0;
        dfs(p);
        cout << ans << '\n';
        for (int i=1;i<=n;++i) {
            g[i].clear();
            uz[i] = false;
        }
    }
    return 0;
}
