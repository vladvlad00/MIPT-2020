#include <bits/stdc++.h>
#define nmax 10005
using namespace std;

char a[111][111];
int n, m, x, y, ca, cb;
bool viz[nmax];
vector<int> g[nmax];
int l[nmax], r[nmax];
bool exists[nmax];

int dl[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

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

int node(int x, int y) {
    return (x - 1) * m + y;
}

int main()
{
    cin >> n >> m >> ca >> cb;

    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            cin >> a[i][j];
        }
    }

    int tot = 0;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            int currentNode = node(i, j);
            if (a[i][j] == '*') {
                ++tot;
            }
            if ((i + j) % 2 == 1) {
                continue;
            }
            if (a[i][j] == '.') {
                continue;
            }
            exists[currentNode] = true;
            for (int k=0;k<4;++k) {
                int ni = i + dl[k];
                int nj = j + dc[k];
                if (a[ni][nj] == '*') {
                    int nnode = node(ni, nj);
                    g[currentNode].push_back(nnode);
                }
            }
        }
    }

    if (cb * 2 <= ca) {
        cout << tot * cb << '\n';
        return 0;
    }

    int num = n * m;
    bool ok = true;
    while (ok) {
        ok = false;
        memset(viz, 0, sizeof(viz));
        for (int i=1;i<=num;++i) {
            if (exists[i] && !viz[i] && !l[i]) {
                if (cup(i)) {
                    ok = true;
                }
            }
        }
    }

    int cupp = 0;
    for (int i=1;i<=num;++i) {
        if (l[i]) {
            ++cupp;
        }
    }
    cout << cupp * ca + (tot - cupp * 2) * cb << '\n';
    return 0;
}
