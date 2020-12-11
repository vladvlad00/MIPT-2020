#include <bits/stdc++.h>
#define nmax 505
using namespace std;

int n1, n2, m;
bool viz[nmax];
vector<int> g[nmax];
int l[nmax], r[nmax];

bool cup(int node) {
    if (node == -1) {
        return false;
    }
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

int cuplaj() {
    bool ok = true;

    while (ok) {
        ok = false;
        memset(viz, 0, sizeof(viz));
        for (int i=1;i<=n1;++i) {
            if (!viz[i] && !l[i]) {
                if (cup(i)) {
                    ok = true;
                }
            }
        }
    }

    int num = 0;
    for (int i=1;i<=n1;++i) {
        if (l[i] > 0) {
            ++num;
        }
    }

    return num;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n1 >> n2 >> m;

    for (int i=1;i<=m;++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
    }

    int maxim = cuplaj();

    for (int i=1;i<=n1;++i) {
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));

        l[i] = -1;
        int cp = cuplaj();
        if (cp == maxim) {
            cout << 'P';
        } else {
            cout << 'N';
        }
    }
    cout << '\n';

    for (int i=1;i<=n2;++i) {
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));

        r[i] = -1;
        int cp = cuplaj();
        if (cp == maxim) {
            cout << 'P';
        } else {
            cout << 'N';
        }
    }
    cout << '\n';

    return 0;
}
