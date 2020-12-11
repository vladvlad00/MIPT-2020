#include <bits/stdc++.h>
#define nmax 1005
using namespace std;

int n, m, x, y;
bool viz[nmax];
vector<int> g[nmax];
int l[nmax], r[nmax];

bool cup(int node) {
    if (viz[node]) {
        return false;
    }
    viz[node] = true;
    for (auto x : g[node]) {
        if (r[x]) {
            continue;
        }
        l[node] = x;
        r[x] = node;
        return true;
    }
    for (auto x : g[node]) {
        if (cup(r[x])) {
            l[node] = x;
            r[x] = node;
            return true;
        }
    }
    return false;
}

int main()
{
    cin >> n >> m;
    for (int i=1;i<=m;++i) {
        cin >> x >> y;
        g[x].push_back(y);
    }

    bool ok = true;
    while (ok) {
        ok = false;
        memset(viz, 0, sizeof(viz));
        for (int i=1;i<=n;++i) {
            if (!viz[i] && !l[i]) {
                if (cup(i)) {
                    ok = true;
                }
            }
        }
    }

    int num = 0;
    for (int i=1;i<=n;++i) {
        if (l[i]) {
            ++num;
        }
    }
    cout << n - num << '\n';
    return 0;
}
