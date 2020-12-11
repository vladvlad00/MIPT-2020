#include <bits/stdc++.h>
#define INF 999999999
#define nmax 205
using namespace std;

bool v[nmax];
int n, us[nmax], x;
vector<int> g[nmax];
int a[nmax][nmax];
int flux[nmax][nmax];
int lst[nmax];
int source, sink;

bool bfs() {
    queue<int> q;
    memset(v, 0, sizeof(v));
    v[source] = true;
    q.push(source);
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
            if (vec == sink) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int ans = 0;
    scanf("%d",&n);
    source = n + 1;
    sink = n + 2;
    for (int i=1;i<=n;++i) {
        scanf("%d",&us[i]);
        if (us[i] > 0) {
            ans += us[i];
        }
    }
    for (int i=1;i<=n;++i) {
        int nr;
        scanf("%d",&nr);
        for (int j=1;j<=nr;++j) {
            scanf("%d",&x);
            g[x].push_back(i);
            g[i].push_back(x);
            a[i][x] += INF;
        }
    }

    for (int i=1;i<=n;++i) {
        if (us[i] >= 0) {
            a[source][i] += abs(us[i]);
            g[source].push_back(i);
            g[i].push_back(source);
        } else {
            a[i][sink] += abs(us[i]);
            g[sink].push_back(i);
            g[i].push_back(sink);
        }
    }

    while (bfs()) {
        int sub = INF;
        int nod = sink;
        while (nod != source) {
            sub = min(sub, a[lst[nod]][nod] - flux[lst[nod]][nod]);
            nod = lst[nod];
        }
        nod = sink;
        ans -= sub;
        while (nod != source) {
            flux[lst[nod]][nod] += sub;
            flux[nod][lst[nod]] -= sub;
            nod = lst[nod];
        }
    }

    printf("%d\n", ans);
    return 0;
}
