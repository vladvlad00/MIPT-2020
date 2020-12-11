#include <bits/stdc++.h>
#define nmax 105
#define INF 999999999
using namespace std;

int n, m, x, y, z;
bool v[nmax];
vector<int> g[nmax];
vector<pair<int,pair<int,int>>> edges;
int a[nmax][nmax];
int flux[nmax][nmax];
int lst[nmax];

bool bfs() {
    queue<int> q;
    memset(v, 0, sizeof(v));
    v[1] = true;
    q.push(1);
    while (!q.empty()) {
        auto act = q.front();
        q.pop();
        for (auto vec : g[act]) {
            if (flux[act][vec] == a[act][vec]) {
                continue;
            }
            if (v[vec]) {
                continue;
            }
            v[vec] = true;
            lst[vec] = act;
            q.push(vec);
            if (vec == n) {
                return true;
            }
        }
    }
    return false;
}
// source - 1
// sink - n
int main()
{
    scanf("%d",&n);
    scanf("%d",&m);
    for (int i=1;i<=m;++i) {
        scanf("%d %d %d",&x,&y,&z);
        a[x][y] += z;
        a[y][x] += z;
        g[x].push_back(y);
        g[y].push_back(x);
        edges.push_back({z, {x, y}});
    }
    int ans = 0;
    while (bfs()) {
        int add = INF;
        int nod = n;
        while (nod != 1) {
            add = min(add, a[lst[nod]][nod] - flux[lst[nod]][nod]);
            nod = lst[nod];
        }
        nod = n;
        ans += add;
        while (nod != 1) {
            flux[lst[nod]][nod] += add;
            flux[nod][lst[nod]] -= add;
            nod = lst[nod];
        }
    }
    printf("%d\n", ans);
    for (auto e : edges) {
        x = e.second.first;
        y = e.second.second;
        z = e.first;
        if (!flux[x][y]) {
            cout << 0 << '\n';
            continue;
        }
        if (flux[x][y] < 0) {
            int af = min(abs(flux[x][y]), z);
            cout << -af << '\n';
            flux[x][y] += af;
            flux[y][x] -= af;
        } else {
            int af = min(flux[x][y], z);
            cout << af << '\n';
            flux[x][y] -= af;
            flux[y][x] += af;
        }
    }
    return 0;
}
