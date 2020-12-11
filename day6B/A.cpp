#include <bits/stdc++.h>
#define nmax 300
using namespace std;

int n, m;
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
        if (cup(x)) {
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
    for (int i=1;i<=n;++i) {
        int x;
        while (true) {
            cin >> x;
            if (!x) {
                break;
            }
            g[i].push_back(x);
        }
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
    cout << num << '\n';
    for (int i=1;i<=n;++i) {
        if (l[i]) {
            cout << i << ' ' << l[i] << '\n';
        }
    }
    return 0;
}
